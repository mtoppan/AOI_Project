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

	UFUNCTION()
	void EndDrum();

	UPROPERTY()
	USoundBase* PickUpDrumSound;

	UFUNCTION()
	void CoolDownEnd();
	bool CooldownActive = false;

	bool FirstTimePickUp = false;

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
	virtual void ResetInstrument() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDrumSound();
	UFUNCTION(BlueprintImplementableEvent)
	void CrackRock();
	UFUNCTION(BlueprintImplementableEvent)
	void AddDrumTrack();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowUI();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDrumIcon();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowMusicClef();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool AddedTrack = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Parameters")
	bool Playing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* SphereCollision;
	

};
