// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyMover.h"

// Sets default values for this component's properties
UKeyMover::UKeyMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    Offset = FVector(0, 0, 10);
    MoveTime = 1;
    KeyPressed = false;
}


// Called when the game starts
void UKeyMover::BeginPlay()
{
	Super::BeginPlay();

    OriginalLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UKeyMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    moveKey(DeltaTime);
}

bool UKeyMover::GetKeyPressed()
{
    return KeyPressed;
}

void UKeyMover::SetKeyPressed(bool IsKeyPressed)
{
    KeyPressed = IsKeyPressed;
}

void UKeyMover::moveKey(float DeltaTime)
{
    FVector TargetLocation = OriginalLocation;
    if (KeyPressed)
    {
        TargetLocation = OriginalLocation + Offset;
    }
    FVector CurrentLocation = GetOwner()->GetActorLocation();
    float Speed = Offset.Length() / MoveTime;

    FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
    GetOwner()->SetActorLocation(NewLocation);
}

