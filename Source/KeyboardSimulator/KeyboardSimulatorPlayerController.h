// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KeyboardSimulatorPlayerController.generated.h"

class UInputMappingContext;
class UMenuWidget;
class UCommissionWidget;
class UScreenWidget;

/**
 *
 */
UCLASS()
class KEYBOARDSIMULATOR_API AKeyboardSimulatorPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    void ToggleMenuWidget();

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

private:
    void InitializeWidgets();

    UPROPERTY(EditDefaultsOnly, Category="Widget")
    TSubclassOf<UMenuWidget> MenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category="Widget")
    TSubclassOf<UCommissionWidget> CommissionWidgetClass;

    UMenuWidget* MenuWidget;
    UCommissionWidget* CommissionWidget;

    UPROPERTY(EditAnywhere, Category="Widget")
    UScreenWidget* ScreenWidget;
	// End Actor interface
};
