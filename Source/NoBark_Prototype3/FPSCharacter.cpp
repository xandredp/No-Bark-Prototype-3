// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "FPSCharacter.h"
#include "GameController.h"
#include "Pickup.h"
#include "HealthPickup.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"


AFPSCharacter::AFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	//FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);


}
void AFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &AFPSCharacter::CollectPickups);

//	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSCharacter::LookUpAtRate);
}

void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::CheckForInteractables()
{
	FHitResult HitResult;
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndTrace = FirstPersonCameraComponent->GetForwardVector() * 300 + StartTrace;

	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);
	
	//AGameController* gameController = Cast<AGameController>(GetController());
	//if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParam) && gameController)
	//{
	//	if (AInteractable * Interactable = Cast<AInteractable>(HitResult.GetActor()))
	//			{
	//		gameController->CurrentInteractable = Interactable;
	//				return;
	//			}
	//}

	//
	//gameController->CurrentInteractable = nullptr;
	//
	//AGameController* Controller = Cast<AGameController>(GetController());
	//if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParam) && Controller)
	//{
	//	if (AInteractable * Interactable = Cast<AInteractable>(HitResult.GetActor()))
	//	{
	//		Controller->CurrentInteractable = Interactable;
	//		return;
	//	}
	//}

	// the thing that hit is not an interactable item set the current interactable to nulll ptr
	//Controller->CurrentInteractable = nullptr;

}

void AFPSCharacter::CollectPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// keep track of the collected battery power
	float CollectedPower = 0;

	// For each Actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast the actor to APickup
		APickup* const TestPickup = Cast<APickup>(CollectedActors[iCollected]);
		// If the cast is successful and the pickup is valid and active 
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsPickupActive())
		{
			// Call the pickup's WasCollected function
			TestPickup->WasCollected();
			// Check to see if the pickup is also a battery
			AHealthPickup* const TestBattery = Cast<AHealthPickup>(TestPickup);
			if (TestBattery)
			{
				// increase the collected power
				CollectedPower += TestBattery->GetPower();
			}
			// Deactivate the pickup 
			TestPickup->SetActive(false);
		}
	}
	if (CollectedPower > 0)
	{
		UpdatePower(CollectedPower);
	}
}

// Reports starting power
float AFPSCharacter::GetInitialPower()
{
	return InitialPower;
}

// Reports current power
float AFPSCharacter::GetCurrentPower()
{
	return CharacterPower;
}

// Reports current power
bool AFPSCharacter::GetLightStatus()
{
	return LightStatus;
}

// called whenever power is increased or decreased
void AFPSCharacter::UpdatePower(float PowerChange)
{
	// change power
	CharacterPower = CharacterPower + PowerChange;
	//// change speed based on power
	//GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + SpeedFactor * CharacterPower;
	// call visual effect
	PowerChangeEffect();
}