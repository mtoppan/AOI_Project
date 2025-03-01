// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"

UENUM()
enum Meters
{
	Four UMETA(DisplayName = "4"),
	Three UMETA(DisplayName = "3")
};

UCLASS()
class AOI_PROJECT_API AMusicManager : public AActor
{
	GENERATED_BODY()

	TArray<FString> BeatFunctionCalls;
	TArray<FString> BeatFunctionCallsArea2;
	int BeatOfMeasure;

	int GraceAmount = 5;
	UFUNCTION()
	void BeatGracePeriodOn();
	UFUNCTION()
	void BeatGracePeriodOff();
	UFUNCTION()
	void GracePeriodOnLoop();
	UFUNCTION()
	void GracePeriodOffLoop();

	void StartSecondAreaMusic(FTimerHandle OldCountTimer, FTimerHandle OldGraceBeatOn, FTimerHandle OldGraceBeatOff);

	FTimerHandle FirstCountTimer;
	FTimerHandle FirstGraceBeatOnTimer;
	FTimerHandle FirstGraceBeatOffTimer;
	
public:	
	// Sets default values for this actor's properties
	AMusicManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
	TEnumAsByte<Meters> MeterTop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
	TEnumAsByte<Meters> MeterBottom;

	bool OnBeat;

	UFUNCTION(BlueprintCallable)
	void DownBeatFired();
	UFUNCTION()
	void SecondBeatFired();
	UFUNCTION()
	void ThirdBeatFired();
	UFUNCTION()
	void FourthBeatFired();
	UFUNCTION()
	void FourthAndBeatFired();
	UFUNCTION()
	void FifthBeatFired();
	UFUNCTION()
	void SixthBeatFired();
	UFUNCTION()
	void SeventhBeatFired();
	UFUNCTION()
	void EighthBeatFired();
	UFUNCTION()
	void DummyBeatFired();

	UFUNCTION(BlueprintCallable)
	void CallSecondMusicTimers();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetRocks();
	UFUNCTION(BlueprintImplementableEvent)
	void ResetRocksSecondSet();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Song Stats")
	float CurrentBPM;

	void CallBlueprintFunction();
	UPROPERTY(EditAnywhere, Category = "BlueprintClass")
    AActor* blueprintActor;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnRocksBeat4Part2Cave();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowRocksBeat4Part2Cave();
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnRocksBeat4Part1Cave();
	UFUNCTION(BlueprintImplementableEvent)
	void SetupSpawns();

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerLights();
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerLightsLowerIntensity();
	UFUNCTION(BlueprintImplementableEvent)
	void PulseRock();
	UFUNCTION(BlueprintImplementableEvent)
	void PulseWater();
	UFUNCTION(BlueprintImplementableEvent)
	void CrystalsPulse();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnFirstRocks();
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnFirstRocksSecondSet();
	UFUNCTION(BlueprintImplementableEvent)
	void RespawnNecessaryRocks();

	// Variables for spawning objects

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Objects")
	TArray<TSubclassOf<AActor>> BPClassesToSpawnBeat1Cave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Objects")
	TArray<TSubclassOf<AActor>> BPClassesToSpawnBeat4Cave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Objects")
	TArray<int> LifeSpansBeat1Cave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Objects")
	TArray<int> LifeSpansBeat4Cave;

	void SetUpSpawning();

	UFUNCTION(BlueprintCallable)
	void BeginGame();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CountBeat();
	UFUNCTION()
	void CountBeatSubdivisions();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int TotalBeatsPlayed = 0;

};
