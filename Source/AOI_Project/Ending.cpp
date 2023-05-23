// Fill out your copyright notice in the Description page of Project Settings.


#include "Ending.h"

#include "BasePlayer.h"

// Sets default values
AEnding::AEnding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnding::BeginPlay()
{
	Super::BeginPlay();
	Sphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEnding::OnOverlapBegin);
}

void AEnding::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
		Player->CanMove = false;
	}
}


// Called every frame
void AEnding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

