// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "KeyboardSimulatorGameMode.h"
#include "KeyboardSimulatorCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

#include "CommissionWidget.h"
#include "ScreenWidget.h"

UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
    bCommissionInProgress = false;
}

void UMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    bCommissionInProgress = false;
    EasyButton->OnClicked.AddDynamic(this, &UMenuWidget::OnEasyButtonPress);
    MediumButton->OnClicked.AddDynamic(this, &UMenuWidget::OnMediumButtonPress);
    HardButton->OnClicked.AddDynamic(this, &UMenuWidget::OnHardButtonPress);
    SubmitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnSubmitButtonPress);

    if (AccuracyText)
    {
        AccuracyText->SetText(FText::AsPercent(1.f));
    }

    GameMode = Cast<AKeyboardSimulatorGameMode>(UGameplayStatics::GetGameMode(this));
}

void UMenuWidget::SetCommissionWidget(UCommissionWidget* TargetWidget)
{
    CommissionWidget = TargetWidget;
}

void UMenuWidget::SetScreenWidget(UScreenWidget* TargetWidget)
{
    ScreenWidget = TargetWidget;
}

void UMenuWidget::OnEasyButtonPress()
{
    if (!bCommissionInProgress)
    {
        bCommissionInProgress = true;
        CommissionWidget->LoadCommission(Difficulty::Easy);
    }
}

void UMenuWidget::OnMediumButtonPress()
{
    if (!bCommissionInProgress)
    {
        bCommissionInProgress = true;
        CommissionWidget->LoadCommission(Difficulty::Medium);
    }
}

void UMenuWidget::OnHardButtonPress()
{
    if (!bCommissionInProgress)
    {
        bCommissionInProgress = true;
        CommissionWidget->LoadCommission(Difficulty::Hard);
    }
}

void UMenuWidget::OnSubmitButtonPress()
{
    if (bCommissionInProgress)
    {
        bCommissionInProgress = false;

        FString OriginalCommission = CommissionWidget->GetCommission();
        CommissionWidget->EndCommission();

        FString CopyCommission = ScreenWidget->GetText();
        ScreenWidget->ResetText();

        float NewAccuracy = GameMode->CalculateAccuracy(OriginalCommission, CopyCommission);
        SetAccuracyText(NewAccuracy);
    }
}

void UMenuWidget::SetAccuracyText(float NewAccuracy)
{
    if(AccuracyText)
    {
        AccuracyText->SetText(FText::AsPercent(NewAccuracy));
    }
}