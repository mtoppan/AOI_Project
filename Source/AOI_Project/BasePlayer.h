// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Collectable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
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
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USceneComponent* PlayerMeshHolder;
	

	UPROPERTY()
	UBoxComponent* BoxCollision;


	UPROPERTY()
	ACollectable* CurrentSelectableInstrument;
	UPROPERTY()
	ACollectable* CurrentUsableInstrument;

	void UseOrSetInstrument();
	UPROPERTY()
	USoundBase* LoseInstrumentSound;
	UFUNCTION()
	void PutInstrumentBack();


public:
	// Sets default values for this character's properties
	ABasePlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GotDrum;
	
	UPROPERTY()
	class UCharacterMovementComponent* Movement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Instruments on Back")
	UStaticMeshComponent* InstrumentOnBack;
	UPROPERTY(EditAnywhere, Category = "Instruments on Back")
	class UStaticMeshComponent* Drum;
	UPROPERTY(EditAnywhere, Category = "Instruments on Back")
	class UStaticMeshComponent* Horn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resetting")
	bool Resetting;
	

	// Camera variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraTurnRate = 0.7f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraLookUpRate = 0.7f;

	UFUNCTION(BlueprintCallable)
	void LoseInstrument();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invincible")
	bool Invincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Grounded;

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

	bool CanMove = true;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayLoseInstrumentSound();

};
