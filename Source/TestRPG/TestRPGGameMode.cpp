// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestRPGGameMode.h"
#include "Character/TestRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestRPGGameMode::ATestRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/Character/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
