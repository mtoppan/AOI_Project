// Fill out your copyright notice in the Description page of Project Settings.


#include "BrassInstrument.h"
#include "BasePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABrassInstrument::ABrassInstrument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrassInstrument::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABrassInstrument::UseInstrument()
{
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	FVector CurrentVelocity = BasePlayer->Movement->Velocity;
	FVector JumpVelocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, JumpForce);
	BasePlayer->Movement->Velocity = JumpVelocity;
	UE_LOG(LogTemp, Warning, TEXT("Use"));
}

// Called every frame
void ABrassInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

