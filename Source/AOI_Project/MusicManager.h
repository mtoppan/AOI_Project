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
	int BeatOfMeasure;
	
public:	
	// Sets default values for this actor's properties
	AMusicManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
	TEnumAsByte<Meters> MeterTop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
	TEnumAsByte<Meters> MeterBottom;


	UFUNCTION()
	void DownBeatFired();
	UFUNCTION()
	void SecondBeatFired();
	UFUNCTION()
	void ThirdBeatFired();
	UFUNCTION()
	void FourthBeatFired();
	UFUNCTION()
	void FifthBeatFired();
	UFUNCTION()
	void SixthBeatFired();
	UFUNCTION()
	void SeventhBeatFired();
	UFUNCTION()
	void EighthBeatFired();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Song Stats")
	float CurrentBPM;

	void CallBlueprintFunction();
	UPROPERTY(EditAnywhere, Category = "BlueprintClass")
    AActor* blueprintActor;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnRocksBeat1Cave();
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnRocksBeat4Cave();
	UFUNCTION(BlueprintImplementableEvent)
	void SetupSpawns();

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CountBeat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
