// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

// Struct of things I can Craft. 
USTRUCT(BlueprintType)
struct FCraftingInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ComponentID; //item used to create Item (  cog)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ProductID; // item that gets created (barrier)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDestroyItemA; // destroy component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDestroyItemB; // destroy product id

};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItem()
	{
		Name = FText::FromString("Item");
		Action = FText::FromString("Use");
		Description = FText::FromString("Description here");
		Value = 10;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class APickup>ItemPickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCraftingInfo> CraftCombinations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeUsed;

	//ureal requires oveloading the data. 
	bool operator == (const FInventoryItem& Item) const
	{
		if (ItemID == Item.ItemID)
			return true;
		else return false;

	}
};



class UInputComponent;

UCLASS(config = Game)
class NOBARK_PROTOTYPE3_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()



	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	AFPSCharacter();

	virtual void BeginPlay();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, Category = Pickup)
		void CheckForInteractables();

protected:

	/** Fires a projectile. */

	UFUNCTION()
	void MoveForward(float Val);
	UFUNCTION()
	void MoveRight(float Val);
	UFUNCTION()
	void TurnAtRate(float Rate);
	UFUNCTION()
	void LookUpAtRate(float Rate);

	

	/**
	Function to update the character's power
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/

public:
	/**Current power level of our character */
	UPROPERTY(EditAnywhere, Category = "Power")
		float CharacterPower;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool LightStatus;

	/** Accessor function for initial power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCurrentPower();

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
		bool GetLightStatus();

	/**
	Function to update the character's power
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdatePower(float PowerChange);

	/** Location on gun mesh where light should spawn. */
	UPROPERTY(EditAnywhere, Category = "PickupMesh")
		class USphereComponent* CollectionSphere;

protected:
	
	/** Called when we press a key to collect any pickups inside the CollectionSphere */
	UFUNCTION(BlueprintCallable, Category = "Pickups")
		void CollectPickups();

	/**The starting power level of our character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialPower;

	/** Multiplier for character speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float LightFactor;

	/** Speed when power level = 0 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float BaseFactor;

	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
		void PowerChangeEffect();

	/**The rate at which the character loses power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float LightingTime;



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
public:

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

