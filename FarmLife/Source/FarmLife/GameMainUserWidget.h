// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
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

	UPROPERTY(meta = (BindWidget))
	UImage* PauseImage;//一時停止用画像


	UPROPERTY(meta = (BindWidget))
	UImage* FilterEffect;//画面フィルターエフェクト

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
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

	//鍬の耐久値更新
	UFUNCTION(BlueprintCallable)
	void UpdateHoeCount(int32 hoe_count, int32 max_hoe_count);

	//画面フィルターカラー設定
	UFUNCTION(BlueprintCallable)
	void ChangeFilterEffect(FVector Color,float Alpha);

	UFUNCTION(BlueprintCallable)
	void ChangeUIImage(UTexture2D* texture);

	//初期色変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor StartColor;

	//終端色変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor EndColor;

	//色の変化させる時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	float LeapTimer;

private:
	FLinearColor now_color;//現在の色
	bool isColorChange = false;//色変更用変数
};