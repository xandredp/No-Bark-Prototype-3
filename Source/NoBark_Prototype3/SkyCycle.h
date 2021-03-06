// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SkyCycle.generated.h"

UCLASS()
class NOBARK_PROTOTYPE3_API ASkyCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkyCycle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION(BlueprintCallable, Category = "Spawning")
		float GetHour();

protected:

	/**Set the amount day time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float Hour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float DayLengthInMins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float OneDay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float OneHour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float valueForLength;

	
};
