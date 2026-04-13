// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CropData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FARMLIFE_API UCropData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	//ì•¨‘Ì—Í
	UPROPERTY(EditAnywhere)
	int32 max_hp = 3;

	//ì•¨‰¿’l
	UPROPERTY(EditAnywhere)
	int32 drop_money = 1;

	//ƒƒbƒVƒ…
	UPROPERTY(EditAnywhere)
	UStaticMesh* mesh;

};
