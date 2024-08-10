// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingHookProjectile.h"
#include "Components/CapsuleComponent.h"
#include "CableComponent.h"
#include "KeyboardSimulatorCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AGrapplingHookProjectile::AGrapplingHookProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
    RootComponent = CollisionComp;

    HookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hook Mesh"));
    HookMesh->SetupAttachment(RootComponent);

    CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("Cable Component"));
    CableComp->SetupAttachment(HookMesh, FName("CableSocket"));

    HookMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Hook Movement Component"));
    HookMovementComp->MaxSpeed = 3000.f;
    HookMovementComp->InitialSpeed = 3000.f;
    HookMovementComp->ProjectileGravityScale = 0;
}

void AGrapplingHookProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    HookMovementComp->StopSimulating(Hit);
    SetActorLocationAndRotation(GetActorTransform().InverseTransformPosition(Hit.ImpactPoint), Hit.ImpactNormal.Rotation());
    AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);

    // Message to GrapplingHookComponent to initiate player movement
    OnHookHitDelegate.ExecuteIfBound(HitComp, Hit);
}

// Called when the game starts or when spawned
void AGrapplingHookProjectile::BeginPlay()
{
	Super::BeginPlay();

    CollisionComp->OnComponentHit.AddDynamic(this, &AGrapplingHookProjectile::OnHit);

    CableComp->SetAttachEndTo(GetOwner(), "FirstPersonCameraComponent");
}

// grapplecable->EndLocation = GetActorTransform().InverseTransformPosition(GrabPoint);