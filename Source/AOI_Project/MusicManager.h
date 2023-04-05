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

	float CurrentBPM;
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

	void CallBlueprintFunction();
	UPROPERTY(EditAnywhere, Category = "BlueprintClass")
		AActor* blueprintActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CountBeat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
