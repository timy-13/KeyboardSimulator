// Fill out your copyright notice in the Description page of Project Settings.


#include "CommissionWidget.h"
#include "Misc/FileHelper.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableTextBox.h"

UCommissionWidget::UCommissionWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
    EasyIndex = 0;
    MediumIndex = 0;
    HardIndex = 0;
}

void UCommissionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CommissionText)
    {
        CommissionText->SetIsReadOnly(true);
    }

    LoadFileLists();
}

void UCommissionWidget::LoadFileLists()
{
    FString Filename = FPaths::ProjectContentDir() + "//Commissions//EasyFileList.txt";
    if (!FFileHelper::LoadFileToStringArray(EasyFileList, *Filename))
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load Easy File List"));
    }

    Filename = FPaths::ProjectContentDir() + "//Commissions//MediumFileList.txt";
    if (!FFileHelper::LoadFileToStringArray(MediumFileList, *Filename))
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load Medium File List"));
    }

    Filename = FPaths::ProjectContentDir() + "//Commissions//HardFileList.txt";
    if (!FFileHelper::LoadFileToStringArray(HardFileList, *Filename))
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load Hard File List"));
    }
}

void UCommissionWidget::LoadCommission(Difficulty CommissionDifficulty)
{
    FString path = FPaths::ProjectContentDir() + "//Commissions//";
    switch (CommissionDifficulty)
    {
    case Difficulty::Easy:
        path += "Easy//" + EasyFileList[EasyIndex] + ".txt";
        EasyIndex++;
        if (EasyIndex == EasyFileList.Num())
        {
            EasyIndex = 0;
        }
        break;
    case Difficulty::Medium:
        path += "Medium//" + MediumFileList[MediumIndex] + ".txt";
        MediumIndex++;
        if (MediumIndex == MediumFileList.Num())
        {
            MediumIndex = 0;
        }
        break;
    case Difficulty::Hard:
        path += "Hard//" + HardFileList[HardIndex] + ".txt";
        HardIndex++;
        if (HardIndex == HardFileList.Num())
        {
            HardIndex = 0;
        }
        break;
    default:
        break;
    }

    FString LoadedCommission;
    if (!FFileHelper::LoadFileToString(LoadedCommission, *path))
    {
        UE_LOG(LogTemp, Error, TEXT("Could not load commission file."));
    }

    SetCommission(LoadedCommission);
}

void UCommissionWidget::EndCommission()
{
    if (CommissionText)
    {
        CommissionText->SetText(FText::FromString(""));
    }
}

FString UCommissionWidget::GetCommission()
{
    return Commission;
}

void UCommissionWidget::SetCommission(const FString& NewCommission)
{
    Commission = NewCommission;
    CommissionText->SetText(FText::FromString(NewCommission));
}