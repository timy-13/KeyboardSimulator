// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseKey.h"

#include "TriggerComponent.h"
#include "KeyMover.h"
#include "ScreenWidget.h"

// Sets default values
ABaseKey::ABaseKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    bTextSent = false;
    TextSendDelay = 0.2f;

    KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
    RootComponent = KeyMesh;

    TriggerComponent = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Component"));
    TriggerComponent->SetupAttachment(KeyMesh, FName("TriggerSocket"));
    TriggerComponent->AttachToComponent(KeyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("TriggerSocket"));

    KeyMover = CreateDefaultSubobject<UKeyMover>(TEXT("Key Mover"));
}

// Called when the game starts or when spawned
void ABaseKey::BeginPlay()
{
	Super::BeginPlay();

    TriggerComponent->OnBeginOverlapDelegate.AddDynamic(this, &ABaseKey::UpdateScreenText);
}

// Called every frame
void ABaseKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ABaseKey::GetKeyName()
{
    return KeyName;
}

void ABaseKey::SetScreenWidget(UScreenWidget* TargetWidget)
{
    ScreenWidget = TargetWidget;
}

void ABaseKey::UpdateScreenText()
{
    if (!bTextSent)
    {
        bTextSent = true;
        ScreenWidget->AppendScreenText(KeyName);

        GetWorldTimerManager().SetTimer(
        TextSentHandle, this, &ABaseKey::EnableSendText, TextSendDelay, false);
    }

}

void ABaseKey::EnableSendText()
{
    bTextSent = false;
}