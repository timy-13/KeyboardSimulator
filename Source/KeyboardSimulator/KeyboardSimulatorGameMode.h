// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KeyboardSimulatorGameMode.generated.h"

UCLASS(minimalapi)
class AKeyboardSimulatorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKeyboardSimulatorGameMode();

    float GetAccuracy();
    void SetAccuracy(float NewAccuracy);

    float CalculateAccuracy(FString Original, FString Copy);

private:
    float Accuracy;
    int CommissionCount;
};



