// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 450.0f;
	SpringArm->bUsePawnControlRotation = true;

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Movement = FindComponentByClass<UCharacterMovementComponent>();
	BoxCollision = FindComponentByClass<UBoxComponent>();
	if (BoxCollision != nullptr)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, & ABasePlayer::OnOverlapBegin);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABasePlayer::OnOverlapEnd);
	}

	CurrentUsableInstrument = nullptr;

	const FString Path = FString::Printf(TEXT("/Game/Sounds/SFX/loseInstrument"));
	LoseInstrumentSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr,*Path));

	TArray<UStaticMeshComponent*> StaticMeshes;
	GetComponents<UStaticMeshComponent>(StaticMeshes);
	
	for (UStaticMeshComponent* Component : StaticMeshes)
	{
		if (Component->ComponentHasTag("Drum"))
		{
			Drum = Component;
		}

		if (Component->ComponentHasTag("Horn"))
		{
			Horn = Component;
		}
	}

	TArray<USceneComponent*> SceneComps;
	GetComponents<USceneComponent>(SceneComps);

	for (USceneComponent* Component : SceneComps)
	{
		if (Component->ComponentHasTag("MeshHolder"))
		{
			PlayerMeshHolder = Component;
		}
	}
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABasePlayer::MoveForward(float InputValue)
{
	if (InputValue != 0 && CanMove)
	{
		FVector CameraForward = SpringArm->GetForwardVector();
		FVector MovementDirection = CameraForward * InputValue;
		MovementDirection.Normalize();
		AddMovementInput(MovementDirection);

		FRotator PlayerRotation = Movement->Velocity.Rotation();
		PlayerRotation.Pitch = 0;
		PlayerRotation.Roll = 0;
		PlayerMeshHolder->SetWorldRotation(PlayerRotation);
	}
}

void ABasePlayer::MoveRight(float InputValue)
{
if (InputValue != 0 && CanMove)
	{
		FVector CameraRight = SpringArm->GetRightVector();
		FVector MovementDirection = CameraRight * InputValue;
		MovementDirection.Normalize();
		AddMovementInput(MovementDirection);

		FRotator PlayerRotation = Movement->Velocity.Rotation();
		PlayerRotation.Pitch = 0;
		PlayerRotation.Roll = 0;
		PlayerMeshHolder->SetWorldRotation(PlayerRotation);
	}
}

void ABasePlayer::CameraLookUp(float InputValue)
{
	//AddControllerPitchInput(InputValue * CameraLookUpRate);

	if (InputValue != 0)
	{
		FVector CameraOffset = SpringArm->GetRelativeTransform().GetLocation();
		FRotator SpringArmRotation = SpringArm->GetComponentRotation();
		SpringArmRotation.Pitch -= InputValue;
		SpringArmRotation.Pitch = FMath::ClampAngle(SpringArmRotation.Pitch, -89, 89);
		CameraOffset = SpringArmRotation.RotateVector(CameraOffset);
		SpringArm->SetRelativeLocation(CameraOffset);
		SpringArm->SetWorldRotation(SpringArmRotation);
	}
}

void ABasePlayer::CameraLookRight(float InputValue)
{
	//AddControllerYawInput(InputValue * CameraTurnRate);

	if (InputValue != 0)
	{
		FVector CameraOffset = SpringArm->GetRelativeTransform().GetLocation();
		FRotator SpringArmRotation = SpringArm->GetComponentRotation();
		SpringArmRotation.Yaw += InputValue;
		CameraOffset = SpringArmRotation.RotateVector(CameraOffset);
		SpringArm->SetRelativeLocation(CameraOffset);
		SpringArm->SetWorldRotation(SpringArmRotation);
	}
}

void ABasePlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->ActorHasTag("Instrument"))
	{
		CurrentSelectableInstrument = (ACollectable*)OtherActor;
		UE_LOG(LogTemp,Log,TEXT("entered"));
	}
}

void ABasePlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor->ActorHasTag("Instrument"))
	{
		CurrentSelectableInstrument = nullptr;
	}
}

void ABasePlayer::UseOrSetInstrument()
{

	// if player is able to pick up an instrument, prioritize picking it up
	if (CurrentSelectableInstrument != nullptr)
	{
		if (CurrentUsableInstrument != nullptr)
		{
			// disregard
			//CurrentUsableInstrument->Destroy();
			InstrumentOnBack->SetVisibility(false);
			//CurrentUsableInstrument = nullptr;
			//CurrentUsableInstrument->SetActorLocation(FVector(0, 0, -10000));
		}
		//CurrentUsableInstrument = nullptr;
		if (CurrentSelectableInstrument != CurrentUsableInstrument)
		{
			GotDrum = true;
			CurrentSelectableInstrument->PickUpInstrument();
		}

		CurrentUsableInstrument = CurrentSelectableInstrument;
		CurrentUsableInstrument->BaseMesh->SetVisibility(false);
		CurrentUsableInstrument->HideEffects();
		
		
		if (InstrumentOnBack != nullptr)
		{
			InstrumentOnBack->SetVisibility(true);
		}

		CurrentSelectableInstrument = nullptr;
	}
	else if (CurrentUsableInstrument != nullptr)
	{
		// if player currently has an instrument, use it

		CurrentSelectableInstrument = nullptr;
		CurrentUsableInstrument->UseInstrument();
		// slight buffer in movement for drum
		AddMovementInput(FVector(0,1,0), 100);
	}

	CurrentSelectableInstrument = nullptr;
}

void ABasePlayer::LoseInstrument()
{
	if (CurrentUsableInstrument != nullptr)
		UGameplayStatics::PlaySound2D(GetWorld(), LoseInstrumentSound, 0.45, 1, 0, nullptr, nullptr);
	
	FTimerDelegate InstrumentDelegate;
	FTimerHandle InstrumentHandle;
	
	InstrumentDelegate.BindUFunction(this, FName("PutInstrumentBack"));
	GetGameInstance()->GetTimerManager().SetTimer(InstrumentHandle, InstrumentDelegate, 1.1, false);
	
	// visibility of mesh on back
	if (InstrumentOnBack != nullptr)
	{
		InstrumentOnBack->ToggleVisibility();
		InstrumentOnBack = nullptr;
	}
	
}

void ABasePlayer::PutInstrumentBack()
{
	// visibility of mesh in world
	if (CurrentUsableInstrument != nullptr)
	{
		CurrentUsableInstrument->BaseMesh->ToggleVisibility();
		CurrentUsableInstrument->ResetInstrument();
		CurrentUsableInstrument->ShowEffects();
		CurrentSelectableInstrument = nullptr;
		CurrentUsableInstrument = nullptr;
		
	}
}


// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind action mappings
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasePlayer::UseOrSetInstrument);

	// bind axis mappings
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
	PlayerInputComponent->BindAxis("CameraLookUp", this, &ABasePlayer::CameraLookUp);
	PlayerInputComponent->BindAxis("CameraLookRight", this, &ABasePlayer::CameraLookRight);

}

