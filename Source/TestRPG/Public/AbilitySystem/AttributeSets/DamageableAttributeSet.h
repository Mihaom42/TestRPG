// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "DamageableAttributeSet.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, CurrentHealth, float, MaxHealth);

UCLASS()
class TESTRPG_API UDamageableAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDamageableAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	FOnHealthChangeDelegate CurrentHealthChanged;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UDamageableAttributeSet, CurrentHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(CurrentHealth);
	float GetCurrentHealth() const;
	void SetCurrentHealth(float NewValue);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UDamageableAttributeSet, MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	float GetMaxHealth() const;
	void SetMaxHealth(float NewValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData CurrentHealth;
};
