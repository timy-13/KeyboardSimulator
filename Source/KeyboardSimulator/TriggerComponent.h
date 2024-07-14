// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "KeyMover.h"
#include "TriggerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginOverlap);

class UKeyMover;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEYBOARDSIMULATOR_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
    UTriggerComponent();

    UPROPERTY(BlueprintAssignable, Category = "Delegates")
    FOnBeginOverlap OnBeginOverlapDelegate;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult);

    UFUNCTION()
    void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void SetMover(UKeyMover* Mover);

private:
    UPROPERTY(EditAnywhere)
    FName CompatibleActorTag;

    UKeyMover* Mover;

    bool KeyPressed() const;
    bool IsCompatibleActor(const AActor* Actor) const;
};
