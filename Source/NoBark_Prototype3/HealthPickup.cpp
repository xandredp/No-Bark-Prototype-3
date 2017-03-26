// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "HealthPickup.h"





//Set default values
AHealthPickup::AHealthPickup()
{
	GetPickupMesh()->SetSimulatePhysics(true);

	//the base power level of the battery
	HealthPickupPower = 150.f;
}


void AHealthPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}

// report the power level of the battery
float AHealthPickup::GetPower()
{
	return HealthPickupPower;
}

