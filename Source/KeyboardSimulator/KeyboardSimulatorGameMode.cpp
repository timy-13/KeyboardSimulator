// Copyright Epic Games, Inc. All Rights Reserved.

#include "KeyboardSimulatorGameMode.h"
#include "KeyboardSimulatorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKeyboardSimulatorGameMode::AKeyboardSimulatorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
