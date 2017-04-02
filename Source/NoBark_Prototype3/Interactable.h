// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class NOBARK_PROTOTYPE3_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
		void Use(APlayerController* Controller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable", Meta = (BlueprintProtected = "true"))
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable", Meta = (BlueprintProtected = "true"))
	FString Action;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	FString GetUseText() const { return FString::Printf(TEXT("%s : Press E to %s"), *Name, *Action); }
	
};
