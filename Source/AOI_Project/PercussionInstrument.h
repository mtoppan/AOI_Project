// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "MusicManager.h"
#include "PercussionInstrument.generated.h"

UCLASS()
class AOI_PROJECT_API APercussionInstrument : public ACollectable
{
	GENERATED_BODY()

	UPROPERTY()
	AMusicManager* MusicManager;
	//UPROPERTY(EditAnywhere, Category = "Collision")
	//class UStaticMeshComponent* CollisionVisual;
	UPROPERTY(EditAnywhere, Category = "Collision")
	class USphereComponent* SphereCollision;

	UFUNCTION()
	void EndDrum();

	bool AddedTrack = false;

public:	
	// Sets default values for this actor's properties
	APercussionInstrument();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseInstrument() override;
	virtual void PickUpInstrument() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDrumSound();
	UFUNCTION(BlueprintImplementableEvent)
	void CrackRock();
	UFUNCTION(BlueprintImplementableEvent)
	void AddDrumTrack();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Parameters")
	bool Playing;

};
