// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class AOI_PROJECT_API ACollectable : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	class UCharacterMovementComponent* CharacterMovement;
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UseInstrument();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
