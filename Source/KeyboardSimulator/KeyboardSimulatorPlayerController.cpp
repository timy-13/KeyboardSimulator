// Copyright Epic Games, Inc. All Rights Reserved.


#include "KeyboardSimulatorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "CommissionWidget.h"
#include "MenuWidget.h"
#include "ScreenWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AKeyboardSimulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

    InitializeWidgets();
}

void AKeyboardSimulatorPlayerController::InitializeWidgets()
{
    if (MenuWidgetClass)
    {
        MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);

        TArray<UUserWidget*> ScreenWidgets;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), ScreenWidgets, UScreenWidget::StaticClass(), false);

        if (ScreenWidgets.Num() > 0)
        {
            ScreenWidget = Cast<UScreenWidget>(ScreenWidgets[0]);
        }

        if(ScreenWidget)
        {
            MenuWidget->SetScreenWidget(ScreenWidget);
        }
    }
    if (CommissionWidgetClass)
    {
        CommissionWidget = CreateWidget<UCommissionWidget>(GetWorld(), CommissionWidgetClass);
        CommissionWidget->AddToViewport();
        MenuWidget->SetCommissionWidget(CommissionWidget);
    }
}

void AKeyboardSimulatorPlayerController::ToggleMenuWidget()
{
    if (MenuWidget)
    {
        if (!MenuWidget->IsInViewport())
        {
            MenuWidget->AddToViewport();
        }

        if (MenuWidget->GetVisibility() == ESlateVisibility::Collapsed)
        {
            MenuWidget->SetVisibility(ESlateVisibility::Visible);

            FInputModeGameAndUI Mode;
            Mode.SetWidgetToFocus(MenuWidget->GetCachedWidget());
            SetInputMode(Mode);
        }
        else
        {
            MenuWidget->SetVisibility(ESlateVisibility::Collapsed);

            FInputModeGameOnly Mode;
            SetInputMode(Mode);
        }
    }
}