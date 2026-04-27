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

	//パークのID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FName ParkID;

	//パークの位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FVector2D PositionGrid;

	//パークの描画名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")

	FText DisplayName;

	//パークの描画説明
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	FText Description;

	//パークの通常アイコン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value_icon")
	UTexture2D* NormalIcon;

	//パークの取得後のアイコン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value_icon")
	UTexture2D* ClickedIcon;

	//パークのタイプ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	ParkType ParkType;

	//強化量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	int32 Value;

	//必要金額
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	int32 Cost;

	//作物クラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TSubclassOf<ABaseCrop> CropClass;

	//作物クラス//腐敗
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TSubclassOf<ABaseCrop> CorruptedCropClass;

	//作物クラス//爆発
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TSubclassOf<ABaseCrop> ExplosiveCropClass;

	//接続するパーク
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TArray<UParkData*> ConnectedPerk;

	//必要パーク
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "value")
	TArray<UParkData*> RequiredPerk;


};