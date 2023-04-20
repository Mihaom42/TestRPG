// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitiesData.generated.h"

UENUM()
enum class EAbilityInput : uint8
{
	None				UMETA(DisplayName = "None"),
	Confirm				UMETA(DisplayName = "Confirm"),
	Cancel				UMETA(DisplayName = "Cancel"),
};

UCLASS()
class TESTRPG_API UAbilitiesData : public UObject
{
	GENERATED_BODY()
	
};
