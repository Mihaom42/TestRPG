// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h" 
#include "Interfaces/DamageableInterface.h"

#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle, 
	Stunned,
	Dead
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamage, float, DamageValue);

UCLASS()
class TESTRPG_API AEnemy : public AActor, public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void InitializeAttributes();
	
	UFUNCTION()
	void ApplyDamage(const float Damage);

	UFUNCTION()
	void SetHealthAndState();

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ApplyStunState();

	UFUNCTION()
	void ApplyIdleState();

	UFUNCTION()
	void ApplyDeadState();

	UFUNCTION()
	void ApplyDestroy();

public:
	UFUNCTION()
	void OnHealthChanged(float CurrentHealthVal, float MaxHealthVal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributesSet")
	class UDamageableAttributeSet* DamageAttribute;

protected:
	/**GAS**/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayEffects")
	TSubclassOf<class UGameplayEffect> StartAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GameplayEffects")
	TSubclassOf<class UGameplayEffect> DamageAttributeEffect;

	/*****/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Characteristic", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY()
	class UHealthBarWidget* EnemyCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TMap<EEnemyState, FText> EnemyStates;

private:
	FTimerHandle StunnedTimerHandle;
	FTimerDelegate StunnedTimerDelegate;

	FTimerHandle IdleTimerHandle;

	FTimerHandle DestroyTimerHandle;
	FTimerDelegate DestroyTimerDelegate;
};
