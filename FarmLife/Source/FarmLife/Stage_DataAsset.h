// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Stage_DataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UStage_DataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//ボタンの位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FVector2D Position;

	//ステージ名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FName Stage_Name;

	//ステージ描画名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FText Stage_Display_Name;

	//ステージの番号
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FText Stage_Number;
};