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

	const FString Path = FString::Printf(TEXT("/Game/Sounds/SFX/getDrum"));
	PickUpDrumSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,*Path));
}

// Called every frame
void APercussionInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BaseMesh->AddRelativeRotation(FRotator(0, 1, 0));
}

void APercussionInstrument::UseInstrument()
{
	// turn visuals on and trigger collision check
	//CollisionVisual->ToggleVisibility();
	if (/*!CooldownActive && */MusicManager->OnBeat)
	{
		ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
		BasePlayer->Invincible = true;
		
		SphereCollision->SetGenerateOverlapEvents(true);

		PlayDrumSound();
		CrackRock();
		Playing = true;
		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;

		if (!AddedTrack)
			ShowMusicClef();

		TimerDelegate.BindUFunction(this, FName("EndDrum"));
		GetGameInstance()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 120 / MusicManager->CurrentBPM, false);

		//CooldownActive = true;
	
		//FTimerDelegate CooldownDelegate;
		//FTimerHandle CooldownHandle;

		//CooldownDelegate.BindUFunction(this, FName("CoolDownEnd"));
		//GetGameInstance()->GetTimerManager().SetTimer(CooldownHandle, CooldownDelegate, 3, false);
	}
	else if (!MusicManager->OnBeat)
	{
		PlayWeakerDrumEffects();
	}
}

void APercussionInstrument::PickUpInstrument()
{
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->InstrumentOnBack = BasePlayer->Drum;
	
	AttachToActor(BasePlayer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UGameplayStatics::PlaySound2D(GetWorld(), PickUpDrumSound, 1, 1, 0, nullptr, nullptr);

	if (!FirstTimePickUp)
	{
		FirstTimePickUp = true;
		ShowUI();
	}

	ShowDrumIcon();
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
	
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->Invincible = false;
	
	if (!AddedTrack)
	{
		AddDrumTrack();
		AddedTrack = true;
	}
}

void APercussionInstrument::CoolDownEnd()
{
	//CooldownActive = false;
}




