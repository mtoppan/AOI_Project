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

	BeatOfMeasure = 2;
	DownBeatFired();
	CountBeat();

	// change these per music piece, assumed base is 1/4
	CurrentBPM = 100;
	MeterTop = Meters::Four;
}

void AMusicManager::CountBeat()
{
	FTimerDelegate BeatTimerDelegate;
	FTimerHandle BeatTimerHandle;
	FTimerDelegate CounterTimerDelegate;
	FTimerHandle CounterTimerHandle;

	FString BeatCallToFire = BeatFunctionCalls[BeatOfMeasure - 1];

	BeatTimerDelegate.BindUFunction(this, FName(BeatFunctionCalls[BeatOfMeasure - 1]));
	GetWorld()->GetTimerManager().SetTimer(BeatTimerHandle, BeatTimerDelegate, 60 / CurrentBPM, false);

	BeatOfMeasure = (BeatOfMeasure  % MeterTop) + 1;

	CounterTimerDelegate.BindUFunction(this, FName("CountBeat"));
	GetWorld()->GetTimerManager().SetTimer(CounterTimerHandle, CounterTimerDelegate, 60 / CurrentBPM, false);
}

void AMusicManager::DownBeatFired()
{
	UE_LOG(LogTemp, Warning, TEXT("1"));
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

