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
	
}

void AGate::OpenGate()
{
	// animation
	// sfx
	// disable collider
}

// called by particles when spline is finished (reached gate)
void AGate::UpdateFlowersComplete()
{
	FlowersComplete++;
	if (FlowersComplete == 3)
	{
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

