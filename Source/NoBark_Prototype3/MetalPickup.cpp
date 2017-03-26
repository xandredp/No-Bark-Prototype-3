// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "MetalPickup.h"



//Set default values
AMetalPickup::AMetalPickup()
{
	GetPickupMesh()->SetSimulatePhysics(true);

	//the base power level of the battery
	MetalPickupPower = 150.f;
}


void AMetalPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}

// report the power level of the battery
float AMetalPickup::GetPower()
{
	return MetalPickupPower;
}


