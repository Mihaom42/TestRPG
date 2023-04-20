// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/DamageableAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"

UDamageableAttributeSet::UDamageableAttributeSet()
{
	
}

void UDamageableAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(ThisClass::StaticClass(),
		GET_MEMBER_NAME_CHECKED(ThisClass, CurrentHealth)))
	{
		CurrentHealth.SetCurrentValue(FMath::Clamp(CurrentHealth.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		CurrentHealth.SetBaseValue(FMath::Clamp(CurrentHealth.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		CurrentHealthChanged.Broadcast(GetCurrentHealth(), GetMaxHealth());
	}
}

float UDamageableAttributeSet::GetCurrentHealth() const
{
	return CurrentHealth.GetCurrentValue();
}

void UDamageableAttributeSet::SetCurrentHealth(float NewValue)
{
	CurrentHealth = NewValue;
}

float UDamageableAttributeSet::GetMaxHealth() const
{
	return MaxHealth.GetCurrentValue();
}

void UDamageableAttributeSet::SetMaxHealth(float NewValue)
{
	MaxHealth = NewValue;
}
