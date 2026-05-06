// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GrobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UGrobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//åoâﬂéûä‘
	UPROPERTY(BlueprintReadWrite)
	int32 g_timer;
	//ç≈ëÂéûä‘
	UPROPERTY(BlueprintReadWrite)
	int32 g_max_timer;

};
