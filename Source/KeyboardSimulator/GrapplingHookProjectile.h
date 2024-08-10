// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrapplingHookProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UCapsuleComponent;
class UCableComponent;
class AKeyboardSimulatorCharacter;

DECLARE_DELEGATE_TwoParams(FOnHookHitSignature, class UPrimitiveComponent*, FHitResult);

UCLASS()
class KEYBOARDSIMULATOR_API AGrapplingHookProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapplingHookProjectile();

    FOnHookHitSignature OnHookHitDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* HookMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCableComponent* CableComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UProjectileMovementComponent* HookMovementComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CollisionComp;

    UPROPERTY(EditDefaultsOnly, Category = "Grappling Hook")
    float HookRadius;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
