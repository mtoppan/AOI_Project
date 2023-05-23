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

	BeatFunctionCallsArea2.Add("DownBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("SecondBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("ThirdBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("FourthBeatFired");
	BeatFunctionCallsArea2.Add("FourthAndBeatFired");
	BeatFunctionCallsArea2.Add("FifthBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("SixthBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("SeventhBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");
	BeatFunctionCallsArea2.Add("EighthBeatFired");
	BeatFunctionCallsArea2.Add("DummyBeatFired");

	CurrentBPM = 100;
	// 10 is equivalent to .1 seconds before and after beat (i.e. total grace period of .2 seconds)
	GraceAmount = 5;
	BeatOfMeasure = 3;
}

void AMusicManager::SetUpSpawning()
{
	
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
}

void AMusicManager::BeginGame()
{
	
	// Timer for calling each beat 
	FTimerDelegate CounterTimerDelegate;

	CounterTimerDelegate.BindUFunction(this, FName("CountBeat"));
	GetWorld()->GetTimerManager().SetTimer(FirstCountTimer, CounterTimerDelegate, 60 / CurrentBPM, true);
	
	
	// Timer that triggers calls for the start of the beat grace period
	FTimerDelegate GraceOnTimerDelegate;
	FTimerHandle GraceOnTimerHandle;

	GraceOnTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOn"));
	GetWorld()->GetTimerManager().SetTimer(GraceOnTimerHandle, GraceOnTimerDelegate, (120 - (CurrentBPM / GraceAmount)) / CurrentBPM, false);

	// Timer that triggers calls for the end of the beat grace period
	FTimerDelegate GraceOffTimerDelegate;
	FTimerHandle GraceOffTimerHandle;

	GraceOffTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOff"));
	GetWorld()->GetTimerManager().SetTimer(GraceOffTimerHandle, GraceOffTimerDelegate, (120 + (CurrentBPM / GraceAmount)) / CurrentBPM, false);

	FTimerDelegate FirstSpawnTimerDelegate;
	FTimerHandle FirstSpawnTimerHandle;
	FTimerDelegate SecondSpawnTimerDelegate;
	FTimerHandle SecondSpawnTimerHandle;
	
	FirstSpawnTimerDelegate.BindUFunction(this, FName("SpawnFirstRocks"));
	GetWorld()->GetTimerManager().SetTimer(FirstSpawnTimerHandle, FirstSpawnTimerDelegate, 60 * 3 / CurrentBPM, false);
	SecondSpawnTimerDelegate.BindUFunction(this, FName("SpawnFirstRocksSecondSet"));
	GetWorld()->GetTimerManager().SetTimer(SecondSpawnTimerHandle, SecondSpawnTimerDelegate, 60 * 7 / CurrentBPM, false);
}


void AMusicManager::StartSecondAreaMusic(FTimerHandle OldCountTimer, FTimerHandle OldGraceBeatOn, FTimerHandle OldGraceBeatOff)
{
	// clear old timers
	GetWorldTimerManager().ClearTimer(OldCountTimer);
	GetWorldTimerManager().ClearTimer(OldGraceBeatOn);
	GetWorldTimerManager().ClearTimer(OldGraceBeatOff);

	CurrentBPM = 140;
	GraceAmount = 5;
	BeatOfMeasure = 1;

	// Timer for calling each beat 
	CountBeatSubdivisions();
	FTimerDelegate CounterTimerDelegate;
	FTimerHandle CounterTimerHandle;
	CounterTimerDelegate.BindUFunction(this, FName("CountBeatSubdivisions"));
	GetWorld()->GetTimerManager().SetTimer(CounterTimerHandle, CounterTimerDelegate, 120 / CurrentBPM, true);
	
	
	// Timer that triggers calls for the start of the beat grace period
	FTimerDelegate GraceOnTimerDelegate;
	FTimerHandle GraceOnTimerHandle;
	
	GraceOnTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOn"));
	GetWorld()->GetTimerManager().SetTimer(GraceOnTimerHandle, GraceOnTimerDelegate, (120 - (CurrentBPM / GraceAmount)) / CurrentBPM, false);

	// Timer that triggers calls for the end of the beat grace period
	FTimerDelegate GraceOffTimerDelegate;
	FTimerHandle GraceOffTimerHandle;
	
	GraceOffTimerDelegate.BindUFunction(this, FName("BeatGracePeriodOff"));
	GetWorld()->GetTimerManager().SetTimer(GraceOffTimerHandle, GraceOffTimerDelegate, (120 + (CurrentBPM / GraceAmount)) / CurrentBPM, false);

}

void AMusicManager::CallSecondMusicTimers()
{
	StartSecondAreaMusic(FirstCountTimer, FirstGraceBeatOnTimer, FirstGraceBeatOffTimer);
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

	TotalBeatsPlayed += 1;
}

void AMusicManager::CountBeatSubdivisions()
{
	// Timer for calling each beat 
	FTimerDelegate BeatTimerDelegate;
	FTimerHandle BeatTimerHandle;

	BeatTimerDelegate.BindUFunction(this, FName(BeatFunctionCallsArea2[BeatOfMeasure - 1]));
	GetWorld()->GetTimerManager().SetTimer(BeatTimerHandle, BeatTimerDelegate, 120 / CurrentBPM, false);

	BeatOfMeasure = (BeatOfMeasure  % 16) + 1;
}

void AMusicManager::BeatGracePeriodOn()
{
	// this function is called after an initial delay, and then calls a looping function every beat

	FTimerDelegate GraceOnTimerDelegate;
	
	GraceOnTimerDelegate.BindUFunction(this, FName("GracePeriodOnLoop"));
	GetWorld()->GetTimerManager().SetTimer(FirstGraceBeatOnTimer, GraceOnTimerDelegate, 120 / CurrentBPM, true);
}

void AMusicManager::BeatGracePeriodOff()
{
	// this function is called after an initial delay greater than BeatGracePeriodOn, and then calls a looping function every beat

	FTimerDelegate GraceOffTimerDelegate;
	
	GraceOffTimerDelegate.BindUFunction(this, FName("GracePeriodOffLoop"));
	GetWorld()->GetTimerManager().SetTimer(FirstGraceBeatOffTimer, GraceOffTimerDelegate, 120 / CurrentBPM, true);
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
	PulseWater();
}

void AMusicManager::SecondBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("2"));
	PulseRock();
}

void AMusicManager::ThirdBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("3"));
	PulseWater();
}

void AMusicManager::FourthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("4"));
	PulseRock();
	ResetRocks();
}

void AMusicManager::FourthAndBeatFired()
{
	//UE_LOG(LogTemp, Warning, TEXT("4.5"));
}

void AMusicManager::FifthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("5"));
	TriggerLightsLowerIntensity();
	PulseWater();
}
void AMusicManager::SixthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("6"));
	PulseRock();
}
void AMusicManager::SeventhBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("7"));
	PulseWater();
}

void AMusicManager::EighthBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("8"));
	PulseRock();
	ResetRocksSecondSet();
}

void AMusicManager::DummyBeatFired()
{
}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

