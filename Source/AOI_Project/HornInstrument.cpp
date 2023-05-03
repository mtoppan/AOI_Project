// Fill out your copyright notice in the Description page of Project Settings.


#include "HornInstrument.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayer.h"

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
	MusicManager = (AMusicManager*)UGameplayStatics::GetActorOfClass(GetWorld(), AMusicManager::StaticClass());

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
	if (MusicManager->OnBeat)
	{
		ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
		PlayHornSound();
		Jump();
		
		Playing = true;
		FTimerDelegate TimerDelegate;
		FTimerHandle TimerHandle;

		if (!AddedTrack)
			ShowMusicClef();

		TimerDelegate.BindUFunction(this, FName("EndHorn"));
		GetGameInstance()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 120 / MusicManager->CurrentBPM, false);

		//CooldownActive = true;
	
		//FTimerDelegate CooldownDelegate;
		//FTimerHandle CooldownHandle;

		//CooldownDelegate.BindUFunction(this, FName("CoolDownEnd"));
		//GetGameInstance()->GetTimerManager().SetTimer(CooldownHandle, CooldownDelegate, 3, false);
	}
	else if (!MusicManager->OnBeat)
	{
		PlayWeakerHornEffects();
	}
}

void AHornInstrument::PickUpInstrument()
{
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->InstrumentOnBack = BasePlayer->Horn;
	BasePlayer->Horn->SetVisibility(true);
	AttachToActor(BasePlayer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UGameplayStatics::PlaySound2D(GetWorld(), PickUpHornSound, 1, 1, 0, nullptr, nullptr);
	BaseMesh->SetVisibility(false);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *BaseMesh->GetName());
	if (!FirstTimePickUp)
	{
		FirstTimePickUp = true;
	}

	ShowHornIcon();
}

void AHornInstrument::ResetInstrument()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	BaseMesh->SetVisibility(true);
	SetActorLocation(StartingLocation);
	AddedTrack = false;
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(Player);
	BasePlayer->Horn->SetVisibility(false);
}

void AHornInstrument::CoolDownEnd()
{
}

void AHornInstrument::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("jump"));
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




