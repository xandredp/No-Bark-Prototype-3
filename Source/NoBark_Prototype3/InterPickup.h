// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "InterPickup.generated.h"

/**
 * 
 */
UCLASS()
class NOBARK_PROTOTYPE3_API AInterPickup : public AInteractable
{
	GENERATED_BODY()


public :
		AInterPickup();

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable", Meta = (BlueprintProtected = "true"))
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable", Meta = (BlueprintProtected = "true"))
		UStaticMeshComponent* PickupMesh;
	
};
