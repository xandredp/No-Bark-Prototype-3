// Fill out your copyright notice in the Description page of Project Settings.

#include "NoBark_Prototype3.h"
#include "SkyCycle.h"


// Sets default values
ASkyCycle::ASkyCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkyCycle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkyCycle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

