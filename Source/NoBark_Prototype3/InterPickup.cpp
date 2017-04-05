// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "InterPickup.h"

AInterPickup::AInterPickup()
{
	PickupMesh = CreateDefaultSubobject < UStaticMeshComponent >(TEXT("PickupMesh"));
	ItemID = FName("PleaseEnterID");
}