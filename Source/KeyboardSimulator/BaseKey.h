// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKey.generated.h"

class UTriggerComponent;
class UKeyMover;
class UScreenWidget;

UCLASS()
class KEYBOARDSIMULATOR_API ABaseKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    FString GetKeyName(); 

    UFUNCTION(BlueprintCallable)
    void SetScreenWidget(UScreenWidget* TargetWidget);

private:
    UFUNCTION()
    void UpdateScreenText();

    void EnableSendText();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* KeyMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UTriggerComponent* TriggerComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UKeyMover* KeyMover;

    UScreenWidget* ScreenWidget;

    UPROPERTY(EditAnywhere, Category = "Key")
    FString KeyName;

    FTimerHandle TextSentHandle;
    bool bTextSent;

    UPROPERTY(EditAnywhere, Category = "Key")
    float TextSendDelay;
};
