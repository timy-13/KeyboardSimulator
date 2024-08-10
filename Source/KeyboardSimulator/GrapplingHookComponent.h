// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GrapplingHookComponent.generated.h"

class AKeyboardSimulatorCharacter;
class AGrapplingHookProjectile;
class UInputAction;

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEYBOARDSIMULATOR_API UGrapplingHookComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrapplingHookComponent();
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
    UInputAction* FireAction;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="Player")
    void InitialAttachHook(AKeyboardSimulatorCharacter* TargetCharacter);

private:
    void Fire();
    bool CheckInRange(const FRotator& SpawnRotation, const FVector& SpawnLocation);

    void SetPlayerMove(UPrimitiveComponent* HitComp, FHitResult HitResult);
    void MovePlayer(float DeltaTime);

    void EndGrapple();

    UPROPERTY(VisibleAnywhere, Category="Projectile")
    AGrapplingHookProjectile* GrapplingHookProjectile;

    UPROPERTY(EditDefaultsOnly, Category="Projectile")
    TSubclassOf<class AGrapplingHookProjectile> GrapplingHookProjectileClass;

    UPROPERTY(EditAnywhere, Category="Projectile")
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, Category="Projectile")
    float CollisionRadius;

    UPROPERTY(EditAnywhere, Category="Projectile")
    float CollisionHalfHeight;

    UPROPERTY(EditDefaultsOnly, Category="Projectile")
    float MaxRange;

    AKeyboardSimulatorCharacter* Character;

    bool bFired;
    bool bPlayerTravelling;

    FVector GrapplePoint;

    UPROPERTY(EditDefaultsOnly, Category="Player")
    float MaxTolerance;

    UPROPERTY(EditDefaultsOnly, Category="Player")
    float PlayerSpeed;
};
