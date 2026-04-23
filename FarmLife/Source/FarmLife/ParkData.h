// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseCrop.h"
#include "Engine/Texture2D.h"
#include "ParkData.generated.h"

UENUM(BluePrintType)
enum class ParkType : uint8
{
	AddTimer,
	ValueMag,
	AddCrop,
	AddAttck,
	AddMaxSize
};

/**
 * 
 */
UCLASS(BlueprintType)
class FARMLIFE_API UParkData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FName ParkID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FVector2D PositionGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")

	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value_icon")
	UTexture2D* NormalIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value_icon")
	UTexture2D* ClickedIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	ParkType ParkType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TSubclassOf<ABaseCrop> CropClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TArray<UParkData*> ConnectedPerk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TArray<UParkData*> RequiredPerk;


};