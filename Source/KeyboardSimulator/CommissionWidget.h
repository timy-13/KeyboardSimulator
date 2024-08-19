// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommissionWidget.generated.h"


enum class Difficulty {
    Easy = 0,
    Medium = 1,
    Hard = 2
};

class UMultiLineEditableTextBox;

/**
 * 
 */
UCLASS()
class KEYBOARDSIMULATOR_API UCommissionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UCommissionWidget(const FObjectInitializer& ObjectInitializer);

public:
    void LoadCommission(Difficulty CommissionDifficulty);
    void EndCommission();

    FString GetCommission();
    void SetCommission(const FString& NewCommission);

private:
    UPROPERTY(BlueprintReadOnly, Category="Components", meta=(BindWidget, AllowPrivateAccess="true"))
    UMultiLineEditableTextBox* CommissionText;

    virtual void NativeConstruct() override;

    void LoadFileLists();

    TArray<FString> EasyFileList;
    TArray<FString> MediumFileList;
    TArray<FString> HardFileList;

    int EasyIndex;
    int MediumIndex;
    int HardIndex;

    FString Commission;
};
