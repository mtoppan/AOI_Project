// Fill out your copyright notice in the Description page of Project Settings.


#include "HornInstrument.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/ITargetPlatform.h"

// Sets default values
AHornInstrument::AHornInstrument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHornInstrument::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = GetActorLocation();

	const FString Path = FString::Printf(TEXT("/Game/Sounds/SFX/getDrum"));
	PickUpHornSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,*Path));

	TArray<UStaticMeshComponent*> StaticMeshes;
	GetComponents<UStaticMeshComponent>(StaticMeshes);
	
	for (UStaticMeshComponent* Component : StaticMeshes)
	{
		if (Component->ComponentHasTag("HornMesh"))
		{
			BaseMesh = Component;
			break;
		}
	}
}

// Called every frame
void AHornInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BaseMesh->AddRelativeRotation(FRotator(0, 1, 0));
}

void AHornInstrument::UseInstrument()
{
	if (MusicManager->OnBeat && CanUseInstrument)
	{
		ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
		
		
		if (BasePlayer->Grounded)
		{
			Jump();
			JumpAnimation();
			PlayHornSound();

			Playing = true;
			FTimerDelegate TimerDelegate;
			FTimerHandle TimerHandle;

			if (!AddedTrack)
				ShowMusicClef();

			TimerDelegate.BindUFunction(this, FName("EndHorn"));
			GetGameInstance()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 120 / MusicManager->CurrentBPM, false);
		}
		else
		{
			PlayWeakerHornSound();
		}
		//CooldownActive = true;
	
		//FTimerDelegate CooldownDelegate;
		//FTimerHandle CooldownHandle;

		//CooldownDelegate.BindUFunction(this, FName("CoolDownEnd"));
		//GetGameInstance()->GetTimerManager().SetTimer(CooldownHandle, CooldownDelegate, 3, false);
	}
	else if (!MusicManager->OnBeat && CanUseInstrument)
	{
		PlayWeakerHornEffects();
		OffBeatPenalty();
	}
}

void AHornInstrument::PickUpInstrument()
{
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->InstrumentOnBack = BasePlayer->Horn;
	
	AttachToActor(BasePlayer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UGameplayStatics::PlaySound2D(GetWorld(), PickUpHornSound, 1, 1, 0, nullptr, nullptr);
	
	if (!FirstTimePickUp)
	{
		FirstTimePickUp = true;
	}

	ShowHornIcon();
}

void AHornInstrument::ResetInstrument()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(StartingLocation);
	AddedTrack = false;
}

void AHornInstrument::CoolDownEnd()
{
}

void AHornInstrument::Jump()
{
	Movement->SetMovementMode(MOVE_Falling);
	FVector CurrentVelocity = Movement->Velocity;
	FVector JumpVelocity = FVector(CurrentVelocity.X,CurrentVelocity.Y, 1000);
	Movement->Velocity = JumpVelocity;
}

void AHornInstrument::EndHorn()
{
	Playing = false;
	
	if (!AddedTrack)
	{
		AddHornTrack();
		AddedTrack = true;
	}
}




