// Fill out your copyright notice in the Description page of Project Settings.


#include "PercussionInstrument.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayer.h"

// Sets default values
APercussionInstrument::APercussionInstrument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Root;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//CollisionVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	//CollisionVisual->SetupAttachment(Root);
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollision->SetupAttachment(Root);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	BaseMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void APercussionInstrument::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();
	MusicManager = (AMusicManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AMusicManager::StaticClass());
}

// Called every frame
void APercussionInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APercussionInstrument::UseInstrument()
{
	// turn visuals on and trigger collision check
	//CollisionVisual->ToggleVisibility();
	SphereCollision->SetGenerateOverlapEvents(true);

	PlayDrumSound();
	CrackRock();
	Playing = true;
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;

	TimerDelegate.BindUFunction(this, FName("EndDrum"));
	GetGameInstance()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 60 / MusicManager->CurrentBPM, false);
}

void APercussionInstrument::PickUpInstrument()
{
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->InstrumentOnBack = BasePlayer->Drum;

	AttachToActor(BasePlayer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APercussionInstrument::ResetInstrument()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(StartingLocation);
	AddedTrack = false;
}

void APercussionInstrument::EndDrum()
{
	// turn visuals off and end collision check
	//CollisionVisual->ToggleVisibility();
	SphereCollision->SetGenerateOverlapEvents(false);
	Playing = false;
	
	if (!AddedTrack)
	{
		AddDrumTrack();
		AddedTrack = true;
	}
}



