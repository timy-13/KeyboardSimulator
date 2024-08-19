// Copyright Epic Games, Inc. All Rights Reserved.

#include "KeyboardSimulatorGameMode.h"
#include "KeyboardSimulatorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AccuracyCalculator.h"

AKeyboardSimulatorGameMode::AKeyboardSimulatorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

    CommissionCount = 0;
    Accuracy = 100.f;
}

float AKeyboardSimulatorGameMode::CalculateAccuracy(FString Original, FString Copy)
{
    CommissionCount++;
    int LevDis = AccuracyCalculator::CalculateLevenshteinDistance(Original, Copy);
    float NewAccuracy = AccuracyCalculator::CalculateAccuracy(LevDis, FMath::Max(Original.Len(), Copy.Len()));
    Accuracy = AccuracyCalculator::CalculateAverageAccuracy(Accuracy, NewAccuracy, CommissionCount);

    return Accuracy;
}

float AKeyboardSimulatorGameMode::GetAccuracy()
{
    return Accuracy;
}

void AKeyboardSimulatorGameMode::SetAccuracy(float NewAccuracy)
{
    Accuracy = NewAccuracy;
}