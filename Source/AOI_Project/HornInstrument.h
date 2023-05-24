// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "HornInstrument.generated.h"

UCLASS()
class AOI_PROJECT_API AHornInstrument : public ACollectable
{
	GENERATED_BODY()
	
	UPROPERTY()
	USoundBase* PickUpHornSound;

	UFUNCTION()
	void CoolDownEnd();
	
	bool CooldownActive = false;

	bool FirstTimePickUp = false;

	void Jump();
	UFUNCTION()
	void EndHorn();

public:	
	// Sets default values for this actor's properties
	AHornInstrument();

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
	void PlayHornSound();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWeakerHornSound();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWeakerHornEffects();
	UFUNCTION(BlueprintImplementableEvent)
	void AddHornTrack();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowUI();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHornIcon();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowMusicClef();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	bool AddedTrack = false;

	UFUNCTION(BlueprintImplementableEvent)
	void JumpAnimation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Parameters")
	bool Playing;
};
