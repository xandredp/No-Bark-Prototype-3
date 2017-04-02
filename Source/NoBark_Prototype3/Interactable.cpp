// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "Interactable.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//imaryActorTick.bCanEverTick = true;

	Name = "Name not set";
	Action = "Interact";

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

