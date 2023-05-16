// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.h"
#include "Collectable.generated.h"

UCLASS()
class AOI_PROJECT_API ACollectable : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AMusicManager* MusicManager;

	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	class UCharacterMovementComponent* Movement;

	FVector StartingLocation;
	bool CanUseInstrument = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseInstrument();
	virtual void PickUpInstrument();
	virtual void ResetInstrument();
	
	virtual void OffBeatPenalty();
	UFUNCTION()
	void PenaltyOver();

	UPROPERTY(EditAnywhere, Category = "Root")
	class USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* BaseMesh;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEffects();
	UFUNCTION(BlueprintImplementableEvent)
	void HideEffects();


};
