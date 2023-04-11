// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetUpSpawning();
}

void AMusicManager::SetUpSpawning()
{
	// classes to spawn are assigned in blueprint

	// locations to spawn them at, moved in scene, should be created here in c++
	USceneComponent* SceneComponent0 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 0"));
	USceneComponent* SceneComponent1 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 1"));
	USceneComponent* SceneComponent2 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 2"));
	SpawnPoints.Add(SceneComponent0);
	SpawnPoints.Add(SceneComponent1);
	SpawnPoints.Add(SceneComponent2);

	// amount of time they should live, these can be added in blueprint
	LifeSpans.Add(4);
	LifeSpans.Add(4);
	LifeSpans.Add(4);
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	BeatFunctionCalls.Add("DownBeatFired");
	BeatFunctionCalls.Add("SecondBeatFired");
	BeatFunctionCalls.Add("ThirdBeatFired");
	BeatFunctionCalls.Add("FourthBeatFired");
	BeatFunctionCalls.Add("FifthBeatFired");
	BeatFunctionCalls.Add("SixthBeatFired");
	BeatFunctionCalls.Add("SeventhBeatFired");
	BeatFunctionCalls.Add("EighthBeatFired");

	CurrentBPM = 100;
	BeatOfMeasure = 2;

	// change these per music piece, assumed base is 1/4
	//MeterTop = Meters::Four;

	DownBeatFired();
	CountBeat();
}

void AMusicManager::CountBeat()
{
	FTimerDelegate BeatTimerDelegate;
	FTimerHandle BeatTimerHandle;

	FString BeatCallToFire = BeatFunctionCalls[BeatOfMeasure - 1];

	BeatTimerDelegate.BindUFunction(this, FName(BeatFunctionCalls[BeatOfMeasure - 1]));
	GetGameInstance()->GetTimerManager().SetTimer(BeatTimerHandle, BeatTimerDelegate, 60 / CurrentBPM, false);

	FTimerDelegate CounterTimerDelegate;
	FTimerHandle CounterTimerHandle;

	CounterTimerDelegate.BindUFunction(this, FName("CountBeat"));
	GetGameInstance()->GetTimerManager().SetTimer(CounterTimerHandle, CounterTimerDelegate, 60 / CurrentBPM, false);

	BeatOfMeasure = (BeatOfMeasure  % 8) + 1;
}

void AMusicManager::CallBlueprintFunction()
{
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("Ball true"));
	if (blueprintActor) {
		blueprintActor->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	}
}

void AMusicManager::DownBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("1"));
	//SpawnRocks();
}

void AMusicManager::SecondBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("2"));
}

void AMusicManager::ThirdBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("3"));
}

void AMusicManager::FourthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("4"));
	SpawnRocks();
}

void AMusicManager::FifthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("5"));
}
void AMusicManager::SixthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("6"));
}
void AMusicManager::SeventhBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("7"));
}
void AMusicManager::EighthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("8"));
}
// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

