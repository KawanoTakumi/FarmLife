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

	//経過時間
	UPROPERTY(BlueprintReadWrite)
	int32 g_timer;
	//最大時間
	UPROPERTY(BlueprintReadWrite)
	int32 g_max_timer;
	//勝敗
	UPROPERTY(BlueprintReadWrite)
	bool isWin = false;
	//採取回数
	UPROPERTY(BlueprintReadWrite)
	int32 g_use_count;
	//ステージ名保存
	UPROPERTY(BlueprintReadWrite)
	int32 g_stage_id;
	//ステージのクリア結果保存
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> g_result_rank;
};