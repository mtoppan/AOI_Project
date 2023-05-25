// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

UCLASS()
class AOI_PROJECT_API AGate : public AActor
{
	GENERATED_BODY()
	
	
	UPROPERTY()
	USphereComponent* Sphere;
	
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

	UFUNCTION(BlueprintImplementableEvent)
	void GateAnimationAndEffects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int FlowersComplete = 0;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
