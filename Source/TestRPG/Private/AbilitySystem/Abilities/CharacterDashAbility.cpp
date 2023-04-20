// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/CharacterDashAbility.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Character.h"
#include "Character/TestRPGCharacter.h"
#include "GameFramework/Actor.h" 

DEFINE_LOG_CATEGORY_STATIC(LogDashAbility, All, All);

UCharacterDashAbility::UCharacterDashAbility()
{

}

void UCharacterDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogDashAbility, Error, TEXT("World is NULL!"));
		return;
	}

	World->GetTimerManager().SetTimer(DashActionTimer, [Character]()
		{
			Character->LaunchCharacter(Character->GetActorRotation().Vector() * 500, false, false);
		}, 0.01f, false, 0.06f);
	
	World->GetTimerManager().SetTimer(UpActionTimer, [Character]()
		{
			Character->LaunchCharacter(FVector(0, 0, 500), false, true);
		}, 0.1f, false, 0.1f);
}

void UCharacterDashAbility::CancelAbility(const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayAbilityActorInfo* AbilityActorInfo,
	const FGameplayAbilityActivationInfo AbilityActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(AbilityHandle, AbilityActorInfo, AbilityActivationInfo, bReplicateCancelAbility);
}

