// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingHookComponent.h"
#include "GrapplingHookProjectile.h"
#include "KeyboardSimulatorCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UGrapplingHookComponent::UGrapplingHookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    MaxRange = 10000.f;
    PlayerSpeed = 2.f;
    MaxTolerance = 200.f;

    CollisionRadius = 20.f;
    CollisionHalfHeight = 10.f;

    bFired = false;
    bPlayerTravelling = false;
}

// Called every frame
void UGrapplingHookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    MovePlayer(DeltaTime);
}


void UGrapplingHookComponent::InitialAttachHook(AKeyboardSimulatorCharacter* TargetCharacter)
{
	Character = TargetCharacter;
    
	// Check that the character is valid, and has no grappling hook yet
	if (Character == nullptr || Character->GetHasGrapplingHook())
	{
		return;
	}

    //AttachToComponent(Character->GetMesh1P(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("GripPoint")));
    Character->SetHasGrapplingHook(true);

    // Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UGrapplingHookComponent::Fire);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UGrapplingHookComponent::EndGrapple);
		}
	}
}

// Spawn projectile if in range
void UGrapplingHookComponent::Fire()
{
    if (bFired || bPlayerTravelling)
    {
        return;
    }
    bFired = true;

    APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
    const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
    const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(SpawnOffset);
    if (!CheckInRange(SpawnRotation, GetComponentLocation()))
    {
        bFired = false;
        return;
    }

    GrapplingHookProjectile = GetWorld()->SpawnActor<AGrapplingHookProjectile>(GrapplingHookProjectileClass, GetComponentLocation(), GetComponentRotation());
    GrapplingHookProjectile->OnHookHitDelegate.BindUObject(this, &UGrapplingHookComponent::SetPlayerMove);
}

// Check if anything is within range to grapple
bool UGrapplingHookComponent::CheckInRange(const FRotator& SpawnRotation, const FVector& SpawnLocation)
{
    FVector End = GetComponentLocation() + (MaxRange * UKismetMathLibrary::GetForwardVector(GetComponentRotation()));

    DrawDebugLine(GetWorld(), GetComponentLocation(), End, FColor::Red, true);
    DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, true, 100);

    FHitResult HitResult;
    return GetWorld()->SweepSingleByChannel(HitResult, GetComponentLocation(), End, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeCapsule(CollisionRadius, CollisionHalfHeight));
}

void UGrapplingHookComponent::SetPlayerMove(UPrimitiveComponent* HitComp, FHitResult HitResult)
{
    bPlayerTravelling = true;

    GrapplePoint = HitResult.ImpactPoint;
    auto MovementComponent = Character->GetCharacterMovement();

    MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UGrapplingHookComponent::MovePlayer(float DeltaTime)
{
    if (bPlayerTravelling)
    {
        if ( Character->GetActorLocation().Equals(GrapplePoint, MaxTolerance))
        {
            EndGrapple();
        }
        else
        {
            FVector NewLocation = FMath::VInterpTo(Character->GetActorLocation(), GrapplePoint, DeltaTime, PlayerSpeed);
            Character->SetActorLocation(NewLocation);
        }
    }
}

void UGrapplingHookComponent::EndGrapple()
{
    bFired = false;
    bPlayerTravelling = false;

    if (!Character->GetCharacterMovement()->IsFalling())
    {
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
    }
    
    if (GrapplingHookProjectile)
    {
        GrapplingHookProjectile->Destroy();
    }
}