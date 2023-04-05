// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	BeatFunctionCalls.Add("DownBeatFired");
	BeatFunctionCalls.Add("SecondBeatFired");
	BeatFunctionCalls.Add("ThirdBeatFired");
	BeatFunctionCalls.Add("FourthBeatFired");

	CurrentBPM = 100;
	BeatOfMeasure = 2;

	// change these per music piece, assumed base is 1/4
	MeterTop = Meters::Four;

	DownBeatFired();

	FTimerDelegate CounterTimerDelegate;
	FTimerHandle CounterTimerHandle;

	CounterTimerDelegate.BindUFunction(this, FName("CountBeat"));
	GetGameInstance()->GetTimerManager().SetTimer(CounterTimerHandle, CounterTimerDelegate, 60 / CurrentBPM, true);
}

void AMusicManager::CountBeat()
{
	FTimerDelegate BeatTimerDelegate;
	FTimerHandle BeatTimerHandle;

	FString BeatCallToFire = BeatFunctionCalls[BeatOfMeasure - 1];

	BeatTimerDelegate.BindUFunction(this, FName(BeatFunctionCalls[BeatOfMeasure - 1]));
	GetGameInstance()->GetTimerManager().SetTimer(BeatTimerHandle, BeatTimerDelegate, 60 / CurrentBPM, false);

	BeatOfMeasure = (BeatOfMeasure  % 4) + 1;
}

void AMusicManager::CallBlueprintFunction() {
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("Ball true"));
	if (blueprintActor) {
		blueprintActor->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	}
}

void AMusicManager::DownBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("1"));
	CallBlueprintFunction();
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
}

// Called every frame
void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

