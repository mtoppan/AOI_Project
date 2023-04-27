// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"

#include "Evaluation/IMovieSceneEvaluationHook.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SetUpSpawning();

	BeatFunctionCalls.Add("DownBeatFired");
	BeatFunctionCalls.Add("SecondBeatFired");
	BeatFunctionCalls.Add("ThirdBeatFired");
	BeatFunctionCalls.Add("FourthBeatFired");
	BeatFunctionCalls.Add("FifthBeatFired");
	BeatFunctionCalls.Add("SixthBeatFired");
	BeatFunctionCalls.Add("SeventhBeatFired");
	BeatFunctionCalls.Add("EighthBeatFired");

	CurrentBPM = 100;
	// 10 is equivalent to .1 seconds before and after beat (i.e. total grace period of .2 seconds)
	GraceAmount = 10;
	BeatOfMeasure = 3;
}

void AMusicManager::SetUpSpawning()
{
	// classes to spawn are assigned in blueprint

	// locations to spawn them at, moved in scene, should be created here in c++
	/*USceneComponent* SceneComponent0 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 0"));
	USceneComponent* SceneComponent1 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 1"));
	USceneComponent* SceneComponent2 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 2"));
	USceneComponent* SceneComponent3 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 3"));
	USceneComponent* SceneComponent4 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 4"));
	USceneComponent* SceneComponent5 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 5"));
	USceneComponent* SceneComponent6 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point 6"));
	SpawnPoints.Add(SceneComponent0);
	SpawnPoints.Add(SceneComponent1);
	SpawnPoints.Add(SceneComponent2);
	SpawnPoints.Add(SceneComponent3);
	SpawnPoints.Add(SceneComponent4);
	SpawnPoints.Add(SceneComponent5);
	SpawnPoints.Add(SceneComponent6);*/

	// amount of time they should live, these can be added in blueprint
}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	//SetupSpawns();
	
	
	// change these per music piece, assumed base is 1/4
	//MeterTop = Meters::Four;

	// Function calls moved to BP
	//DownBeatFired();
	//CountBeat();

	// Timer for calling each beat 
	FTimerDelegate CounterTimerDelegate;
	FTimerHandle CounterTimerHandle;
	CounterTimerDelegate.BindUFunction(this, FName("CountBeat"));
	GetGameInstance()->GetTimerManager().SetTimer(CounterTimerHandle, CounterTimerDelegate, 60 / CurrentBPM, true);
	
	
	// Timer that triggers calls for the start of the beat grace period
	FTimerDelegate GraceOnTimerDelegate;
	FTimerHandle GraceOnTimerHandle;
	
	GraceOnTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOn"));
	GetWorld()->GetTimerManager().SetTimer(GraceOnTimerHandle, GraceOnTimerDelegate, (60 - (CurrentBPM / GraceAmount)) / CurrentBPM, false);

	// Timer that triggers calls for the end of the beat grace period
	FTimerDelegate GraceOffTimerDelegate;
	FTimerHandle GraceOffTimerHandle;
	
	GraceOffTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOff"));
	GetWorld()->GetTimerManager().SetTimer(GraceOffTimerHandle, GraceOffTimerDelegate, (60 + (CurrentBPM / GraceAmount)) / CurrentBPM, false);

	FTimerDelegate FirstSpawnTimerDelegate;
	FTimerHandle FirstSpawnTimerHandle;
	FTimerDelegate SecondSpawnTimerDelegate;
	FTimerHandle SecondSpawnTimerHandle;
	
	FirstSpawnTimerDelegate.BindUFunction(this, FName("SpawnFirstRocks"));
	GetWorld()->GetTimerManager().SetTimer(FirstSpawnTimerHandle, FirstSpawnTimerDelegate, 60 * 3 / CurrentBPM, false);
	//SecondSpawnTimerDelegate.BindUFunction(this, FName("SpawnFirstRocks"));
	//GetWorld()->GetTimerManager().SetTimer(SecondSpawnTimerHandle, SecondSpawnTimerDelegate, 60 * 7 / CurrentBPM, false);
}

void AMusicManager::CountBeat()
{
	// Timer for calling each beat 
	FTimerDelegate BeatTimerDelegate;
	FTimerHandle BeatTimerHandle;

	FString BeatCallToFire = BeatFunctionCalls[BeatOfMeasure - 1];

	BeatTimerDelegate.BindUFunction(this, FName(BeatFunctionCalls[BeatOfMeasure - 1]));
	GetWorld()->GetTimerManager().SetTimer(BeatTimerHandle, BeatTimerDelegate, 60 / CurrentBPM, false);

	BeatOfMeasure = (BeatOfMeasure  % 8) + 1;
}

void AMusicManager::BeatGracePeriodOn()
{
	// this function is called after an initial delay, and then calls a looping function every beat

	FTimerDelegate GraceOnTimerDelegate;
	FTimerHandle GraceOnTimerHandle;
	
	GraceOnTimerDelegate.BindUFunction(this, FName("GracePeriodOnLoop"));
	GetWorld()->GetTimerManager().SetTimer(GraceOnTimerHandle, GraceOnTimerDelegate, 60 / CurrentBPM, true);
}

void AMusicManager::BeatGracePeriodOff()
{
	// this function is called after an initial delay greater than BeatGracePeriodOn, and then calls a looping function every beat

	FTimerDelegate GraceOffTimerDelegate;
	FTimerHandle GraceOffTimerHandle;
	
	GraceOffTimerDelegate.BindUFunction(this, FName("GracePeriodOffLoop"));
	GetWorld()->GetTimerManager().SetTimer(GraceOffTimerHandle, GraceOffTimerDelegate, 60 / CurrentBPM, true);
}

void AMusicManager::GracePeriodOnLoop()
{
	// this function loops to turn on the grace period
	OnBeat = true;
	
}

void AMusicManager::GracePeriodOffLoop()
{
	// this function loops to turn off the grace period
	OnBeat = false;
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
	TriggerLights();
}

void AMusicManager::SecondBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("2"));
	PulseRock();
}

void AMusicManager::ThirdBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("3"));
}

void AMusicManager::FourthBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("4"));
	PulseRock();
	//RespawnNecessaryRocks();
	ResetRocks();
	//SpawnRocksBeat4Part1Cave();
	//SpawnRocksBeat4Part2Cave();
}

void AMusicManager::FifthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("5"));
	TriggerLightsLowerIntensity();
}
void AMusicManager::SixthBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("6"));
	PulseRock();
}
void AMusicManager::SeventhBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("7"));
}
void AMusicManager::EighthBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("8"));
	PulseRock();
	//RespawnNecessaryRocks();
	//SpawnRocksBeat4Part1Cave();
	//SpawnRocksBeat4Part2Cave();
}
// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

