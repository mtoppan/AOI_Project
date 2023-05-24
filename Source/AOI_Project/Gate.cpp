// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
	Sphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnOverlapBegin);
	FlowersComplete = 0;
}

void AGate::OpenGate()
{
	// animation -> communicate with anim BP
	// sfx
	// disable collider

	GateAnimationAndEffects();
}

// called by particles when spline is finished (reached gate)
void AGate::UpdateFlowersComplete()
{

	/*
	 * UPDATE FLOWER EFFECTS SHOULD
	 * play sfx
	 * play niagara at the specified location (where most recent spline went)
	 */
	UpdateFlowerEffects();
	
	FlowersComplete++;
	if (FlowersComplete == 3)
	{
		/*
		 * FINAL FLOWER EFFECTS SHOULD
		 * play sfx
		 * play final niagara and present visual change
		 */
		FinalFlowerEffects();
		
		// wait for player to get close to gate
		GateUnlocked = true;
	}
}

void AGate::EndGame()
{
	// TODO
}

void AGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// open the gate when all particles have been collected and the the player gets close to the gate
	if (OtherActor != nullptr && OtherActor->ActorHasTag(FName("Player")) && GateUnlocked && !GateOpened)
	{
		OpenGate();
		GateOpened = true;
	}
}


// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

