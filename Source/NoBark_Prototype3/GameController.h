// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "GameController.generated.h"

/**
 * 
 */
UCLASS()
class NOBARK_PROTOTYPE3_API AGameController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// This is used in player for items looked at. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	class AInteractable* CurrentInteractable;


	
	
};
