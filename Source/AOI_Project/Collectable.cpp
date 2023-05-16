// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "BasePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StartingLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	//cant do this without #include - circular dependency
	Player = UGameplayStatics::GetActorOfClass(GetWorld(), ABasePlayer::StaticClass());
	Movement = Cast<UCharacterMovementComponent>(Player->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	MusicManager = (AMusicManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AMusicManager::StaticClass());
}

// create a child script where you can make this more specific, like editing player movement to add a jump
void ACollectable::UseInstrument()
{
}

void ACollectable::PickUpInstrument()
{
}

void ACollectable::ResetInstrument()
{
}

void ACollectable::OffBeatPenalty()
{
	// temporarily fade away the UI, or otherwise make it clear the player cannot use the instrument
	// disable player from using instrument

	CanUseInstrument = false;
	int BPM = MusicManager->CurrentBPM;

	FTimerHandle PenaltyHandle;
	GetWorld()->GetTimerManager().SetTimer(PenaltyHandle, this, &ACollectable::PenaltyOver, (120.0 / BPM) * 2, false);
	
}

void ACollectable::PenaltyOver()
{
	CanUseInstrument = true;
	UE_LOG(LogTemp, Log, TEXT("can play"));
}



// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

