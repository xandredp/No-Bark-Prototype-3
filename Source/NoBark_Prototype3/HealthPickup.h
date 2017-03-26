// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class NOBARK_PROTOTYPE3_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
	AHealthPickup();

	/** Override the WasCollected function - use Implementation because it's a Blueprint Native Event */
	void WasCollected_Implementation() override;
	/**Public way to access the battery's power level */
	float GetPower();

protected:
	/**Set the amount of power the battery gives to the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float HealthPickupPower;
	
};
