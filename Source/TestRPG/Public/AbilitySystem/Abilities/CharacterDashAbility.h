// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterDashAbility.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UCharacterDashAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCharacterDashAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayAbilityActorInfo* AbilityActorInfo,
		const FGameplayAbilityActivationInfo AbilityActivationInfo, bool bReplicateCancelAbility) override;

private:
	FTimerHandle DashActionTimer;
	FTimerHandle UpActionTimer;
};
