// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

UCLASS()
class AOI_PROJECT_API AGate : public AActor
{
	GENERATED_BODY()

	int FlowersComplete = 0;
	bool GateUnlocked, GateOpened;
	void OpenGate();
	void EndGame();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AGate();
	
	UFUNCTION(BlueprintCallable)
	void UpdateFlowersComplete();
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFlowerEffects();
	UFUNCTION(BlueprintImplementableEvent)
	void FinalFlowerEffects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
