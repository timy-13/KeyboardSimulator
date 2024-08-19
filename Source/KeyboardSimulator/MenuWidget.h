// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommissionWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UButton;
class AKeyboardSimulatorGameMode;
class UCommmissionWidget;
class UScreenWidget;

/**
 * 
 */
UCLASS()
class KEYBOARDSIMULATOR_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UMenuWidget(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetCommissionWidget(UCommissionWidget* TargetWidget);

    UFUNCTION(BlueprintCallable)
    void SetScreenWidget(UScreenWidget* ScreenWidget);

private:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnEasyButtonPress();

    UFUNCTION()
    void OnMediumButtonPress();

    UFUNCTION()
    void OnHardButtonPress();

    UFUNCTION()
    void OnSubmitButtonPress();

    bool bCommissionInProgress;

    void SetAccuracyText(float NewAccuracy);

    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UTextBlock* AccuracyText;

    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UButton* EasyButton;

    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UButton* MediumButton;

    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UButton* HardButton;

    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UButton* SubmitButton;

    UCommissionWidget* CommissionWidget;
    UScreenWidget* ScreenWidget;

    AKeyboardSimulatorGameMode* GameMode;
};