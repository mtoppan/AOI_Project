// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "BrassInstrument.generated.h"

UCLASS()
class AOI_PROJECT_API ABrassInstrument : public ACollectable
{
	GENERATED_BODY()

	float JumpForce = 10000;
	
public:	
	// Sets default values for this actor's properties
	ABrassInstrument();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseInstrument() override;

};
