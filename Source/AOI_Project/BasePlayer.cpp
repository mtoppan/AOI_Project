// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayer::MoveForward(float InputValue)
{
	if (Controller != NULL && InputValue != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement input
		AddMovementInput(Direction, InputValue);

	}
}

void ABasePlayer::MoveRight(float InputValue)
{
	if (Controller != NULL && InputValue != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement input
		AddMovementInput(Direction, InputValue);

	}
}

void ABasePlayer::CameraLookUp(float InputValue)
{
	AddControllerPitchInput(InputValue * CameraLookUpRate);
}

void ABasePlayer::CameraLookRight(float InputValue)
{
	AddControllerYawInput(InputValue * CameraTurnRate);
}

void ABasePlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->ActorHasTag("Instrument"))
	{
		CurrentSelectableInstrument = (ACollectable*)OtherActor;
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
	// if player currently has an instrument, use it
	// access methods from CurrentUsableInstrument
	if (CurrentUsableInstrument != nullptr)
	{
		//InstrumentOnBack->ToggleVisibility();
		CurrentUsableInstrument->UseInstrument();
	}

	// if player doesn't currently have an instrument, try to pick one up
	if (CurrentSelectableInstrument != nullptr)
	{
		// may want to change this to a type later, enum?
		CurrentUsableInstrument = CurrentSelectableInstrument;
		CurrentUsableInstrument->FindComponentByClass<UStaticMeshComponent>()->ToggleVisibility();
		//InstrumentOnBack->ToggleVisibility();
	}
}


// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind action mappings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasePlayer::UseOrSetInstrument);

	// bind axis mappings
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
	PlayerInputComponent->BindAxis("CameraLookUp", this, &ABasePlayer::CameraLookUp);
	PlayerInputComponent->BindAxis("CameraLookRight", this, &ABasePlayer::CameraLookRight);

}

