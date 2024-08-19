// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"

class UMultiLineEditableTextBox;

/**
 * 
 */
UCLASS()
class KEYBOARDSIMULATOR_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AppendScreenText(FString NewText);

    UFUNCTION(BlueprintCallable)
    void ResetText();

    FString GetText();

private:
    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UMultiLineEditableTextBox* ScreenText;

    FString CurrentText;
};
