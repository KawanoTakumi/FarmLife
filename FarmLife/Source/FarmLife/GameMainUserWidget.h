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
	UTextBlock* MoneyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorldTimerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UseHoeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHoeText;

	virtual void NativeConstruct() override;

public:
	//お金更新関数
	UFUNCTION(BlueprintCallable)
	void UpdateMeoney(int32 money);

	//残り時間更新関数
	UFUNCTION(BlueprintCallable)
	void UpdateTimer(int32 timer);

	//ワールドの残り時間作成
	UFUNCTION(BlueprintCallable)
	void UpdateWorldTimer(int32 worldtimer);

	UFUNCTION(BlueprintCallable)
	void UpdateHoeCount(int32 hoe_count, int32 max_hoe_count);

};