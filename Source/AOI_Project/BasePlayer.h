// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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


public:
	// Sets default values for this character's properties
	ABasePlayer();

	// Camera variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement functions
	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void CameraLookUp(float InputValue);
	void CameraLookRight(float InputValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
