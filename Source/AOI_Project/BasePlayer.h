// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Collectable.h"
#include "Components/BoxComponent.h"
#include "BasePlayer.generated.h"

UCLASS()
class AOI_PROJECT_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

	// Camera defaults
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
	UPROPERTY()
	class UCharacterMovementComponent* Movement;
	UPROPERTY()
	UBoxComponent* BoxCollision;
	UPROPERTY()
	UStaticMeshComponent* InstrumentOnBack;


	UPROPERTY()
	ACollectable* CurrentSelectableInstrument;
	UPROPERTY()
	ACollectable* CurrentUsableInstrument;

	void UseOrSetInstrument();


public:
	// Sets default values for this character's properties
	ABasePlayer();

	// Camera variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraTurnRate = 0.7f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraLookUpRate = 0.7f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement functions
	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void CameraLookUp(float InputValue);
	void CameraLookRight(float InputValue);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
