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

public : 

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	AFPSCharacter();

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		float BaseLookUpRate;



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
	UFUNCTION()
	void CheckForInteractables();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
public:

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

