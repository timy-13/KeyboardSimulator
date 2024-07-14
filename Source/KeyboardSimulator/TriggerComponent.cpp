// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

#include "KeyMover.h"


UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnTriggerBeginOverlap);
    OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnTriggerEndOverlap);
    //OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnTriggerEndOverlap);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // if (KeyPressed())
    // {
    //     Mover->SetKeyPressed(true);
    // }
    // else
    // {
    //     Mover->SetKeyPressed(false);
    // }
}

void UTriggerComponent::SetMover(UKeyMover* NewMover)
{
    Mover = NewMover;
}

bool UTriggerComponent::KeyPressed() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(CompatibleActorTag))
        {
            return true;
        }
    }

    return false;
}

bool UTriggerComponent::IsCompatibleActor(const AActor* Actor) const
{
    if (Actor->ActorHasTag(CompatibleActorTag))
    {
        return true;
    }
    return false;
}

void UTriggerComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor != nullptr && OtherComp != nullptr && IsCompatibleActor(OtherActor) == true)
    {
        Mover->SetKeyPressed(true);
        OnBeginOverlapDelegate.Broadcast();
    }
}

void UTriggerComponent::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor != nullptr && OtherComp != nullptr && IsCompatibleActor(OtherActor) == true)
    {
        Mover->SetKeyPressed(false);
    }
}