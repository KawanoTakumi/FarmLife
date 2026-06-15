// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SpawnField.h"
#include "GameMainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UGameMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyText;//お金表示

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;//時間表示

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorldTimerText_Second;//制限時間表示（秒）

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorldTimerText_Min;//制限時間表示（分）

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UseHoeText;//鍬の耐久値

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHoeText;//鍬の最大耐久値

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestMoneyText;//クリアに必要な金額

	virtual void NativeConstruct() override;
public:
	//お金更新関数
	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int32 money);

	UFUNCTION(BlueprintCallable)
	void SetQuestMoney(int32 quest_money);

	//残り時間更新関数
	UFUNCTION(BlueprintCallable)
	void UpdateTimer(int32 timer);

	//ワールドの残り時間作成
	UFUNCTION(BlueprintCallable)
	void UpdateWorldTimer(int32 worldtimer);

	UFUNCTION(BlueprintCallable)
	void UpdateHoeCount(int32 hoe_count, int32 max_hoe_count);
};