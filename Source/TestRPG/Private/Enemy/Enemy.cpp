// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "GameplayEffectTypes.h" 
#include "Abilities/GameplayAbility.h" 
#include "AbilitySystemComponent.h" 
#include "AbilitySystem/AttributeSets/DamageableAttributeSet.h"
#include "AbilitySystem/DamageTypes/DashDamageType.h"
#include "Engine/DamageEvents.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/WidgetComponent.h" 
#include "Components/CapsuleComponent.h" 
#include "UI/HealthBarWidget.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogEnemy, All, All);

// Sets default values
AEnemy::AEnemy()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	DamageAttribute = CreateDefaultSubobject<UDamageableAttributeSet>(TEXT("DamageableAttributeSet"));
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(MeshComponent);
	
	//CapsuleComponent->SetupAttachment(MeshComponent);

	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 0;
	CurrentHealth = 0;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	DamageAttribute->SetMaxHealth(MaxHealth);
	DamageAttribute->SetCurrentHealth(CurrentHealth);

	SetHealthAndState();
	InitializeAttributes();

	DamageAttribute->CurrentHealthChanged.AddDynamic(this, &AEnemy::OnHealthChanged);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::InitializeAttributes()
{
	if (AbilitySystemComponent && StartAttributeEffect)
	{
		// Context Handle is an information about the context in which we are applying an effect
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(StartAttributeEffect, 1, EffectContext);

		// Applies defaults values to a player
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		else
		{
			UE_LOG(LogEnemy, Error, TEXT("SpecHandle is invalid!"));
		}
	}
	else
	{
		UE_LOG(LogEnemy, Error, TEXT("AbilitySystemComponent or StartAttributeEffect is NULL!"));
	}
}

float AEnemy::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (UDashDamageType* DamageType = Cast<UDashDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject()))
	{
		FGameplayEffectSpecHandle EffectSpecHandle =
			AbilitySystemComponent->MakeOutgoingSpec(DamageType->DamageGameplayEffect, 1.0f, FGameplayEffectContextHandle());

		FGameplayEffectSpecHandle GameplayEffectSpecHandle = UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			EffectSpecHandle, DamageType->DamageGameplayTag, Damage * (-1.0f));

		if (GameplayEffectSpecHandle.IsValid())
		{
			ApplyDamage(Damage);
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
		}
		else
		{
			UE_LOG(LogEnemy, Error, TEXT("GameplayEffectSpecHandle is invalid!"));
		}
	}

	return ActualDamage;
}

void AEnemy::OnHealthChanged(float CurrentHealthVal, float MaxHealthVal)
{
	if (EnemyCondition)
	{
		EnemyCondition->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
	else
	{
		UE_LOG(LogEnemy, Error, TEXT("HealthValue is NULL!"));
	}

	if (CurrentHealth != 0)
	{
		ApplyStunState();
	}
	else
	{
		ApplyDeadState();
	}
}

void AEnemy::ApplyDamage(const float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Damage, 0.0f, MaxHealth);
}

void AEnemy::SetHealthAndState()
{
	EnemyCondition = Cast<UHealthBarWidget>(HealthBarWidget->GetUserWidgetObject());

	if (EnemyCondition)
	{
		EnemyCondition->UpdateHealthBar(DamageAttribute->GetCurrentHealth(), DamageAttribute->GetMaxHealth());
		EnemyCondition->UpdateEnemyState(*EnemyStates.Find(EEnemyState::Idle));
	}
	else
	{
		UE_LOG(LogEnemy, Error, TEXT("HealthValue is NULL!"));
	}
}

void AEnemy::ApplyStunState()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogEnemy, Error, TEXT("World is NULL!"));
		return;
	}
	
	StunnedTimerDelegate.BindUFunction(this, FName("ApplyIdleState"));
	World->GetTimerManager().SetTimer(StunnedTimerHandle, StunnedTimerDelegate, 1.0f, false, 5.0f);

	EnemyCondition->UpdateEnemyState(*EnemyStates.Find(EEnemyState::Stunned));
}

void AEnemy::ApplyIdleState()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogEnemy, Error, TEXT("World is NULL!"));
		return;
	}

	World->GetTimerManager().SetTimer(IdleTimerHandle, [&]()
		{
			EnemyCondition->UpdateEnemyState(*EnemyStates.Find(EEnemyState::Idle));
		}, 0.01f, false, 0.01f);
}

void AEnemy::ApplyDeadState()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogEnemy, Error, TEXT("World is NULL!"));
		return;
	}

	StunnedTimerDelegate.BindUFunction(this, FName("ApplyDestroy"));
	World->GetTimerManager().SetTimer(StunnedTimerHandle, StunnedTimerDelegate, 1.0f, false, 2.5f);

	EnemyCondition->UpdateEnemyState(*EnemyStates.Find(EEnemyState::Dead));
}

void AEnemy::ApplyDestroy()
{
	Destroy();
}