// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseCrop.h"
#include "ParkData.generated.h"

UENUM(BluePrintType)
enum class ParkType : uint8
{
	AddTimer,
	ValueMag,
	AddCrop,
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "name")
	FName ParkName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "name")
	ParkType ParkType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "crop")
	TSubclassOf<ABaseCrop> CropClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "tree")
	TArray<UParkData*> NextParkData;
};