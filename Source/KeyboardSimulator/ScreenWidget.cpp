// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidget.h"
#include "Components/MultiLineEditableTextBox.h"

void UScreenWidget::AppendScreenText(FString NewText)
{
    CurrentText.Append(NewText);
    ScreenText->SetText(FText::FromString(CurrentText));
}

void UScreenWidget::ResetText()
{
    ScreenText->SetText(FText::FromString(""));
}

FString UScreenWidget::GetText()
{
    return CurrentText;
}