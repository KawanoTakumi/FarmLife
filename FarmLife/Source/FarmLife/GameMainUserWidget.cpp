// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMainUserWidget.h"

//Start関数
void UGameMainUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

//Tick関数
void UGameMainUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	//時間を取得し、そこから値を取る
	float Time = GetWorld()->GetTimeSeconds();
	float Alpha = (FMath::Sin(Time * LeapTimer) + 1.0f) * 0.5f;

	//設定された初期色と終端色をLeap補完でなめらかに変化させる
	if (isColorChange)
	{
		now_color = FLinearColor::LerpUsingHSV(StartColor, EndColor, Alpha);
	}
		
	else
		now_color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//作成した色を適用
	UseHoeText->SetColorAndOpacity(now_color);
}

void UGameMainUserWidget::SetQuestMoney(int32 money)
{
	if (QuestMoneyText)
	{
		QuestMoneyText->SetText(FText::AsNumber(money));
	}
}

//お金表示更新
void UGameMainUserWidget::UpdateMoney(int32 money)
{
	if (MoneyText)
	{
		MoneyText->SetText(FText::AsNumber(money));
	}
}

//時間表示更新
void UGameMainUserWidget::UpdateTimer(int32 timer)
{
	if (TimerText)
	{
		TimerText->SetText(FText::AsNumber(timer));
	}

}

//世界の時間表示更新
void UGameMainUserWidget::UpdateWorldTimer(int32 worldTimer)
{
	int min = worldTimer / 60;
	int second = worldTimer - (min * 60);

	if (WorldTimerText_Min)
	{
		WorldTimerText_Min->SetText(FText::AsNumber(min));
	}
	if (WorldTimerText_Second)
	{
		WorldTimerText_Second->SetText(FText::AsNumber(second));
	}

}

//鍬の使用・最大使用回数更新
void UGameMainUserWidget::UpdateHoeCount(int32 hoe_count, int32 max_hoe_count)
{
	//使用回数が最大回数の1/4になったら色を変える
	if (hoe_count < (max_hoe_count / 4))
		isColorChange = true;
	else
		isColorChange = false;

	if (UseHoeText)
		UseHoeText->SetText(FText::AsNumber(hoe_count));
	if (MaxHoeText)
		MaxHoeText->SetText(FText::AsNumber(max_hoe_count));
}

//画面のフィルター色を設定
void UGameMainUserWidget::ChangeFilterEffect(FVector Color,float Alpha)
{
	if (FilterEffect)
	{
		//VectorをFLinearColorに変換
		FLinearColor NewColor;
		NewColor.R = Color.X;
		NewColor.G = Color.Y;
		NewColor.B = Color.Z;
		NewColor.A = Alpha;

		//色を設定
		FilterEffect->SetColorAndOpacity(NewColor);

	}
}

void UGameMainUserWidget::ChangeUIImage(UTexture2D* texture)
{
	PauseImage->SetBrushFromTexture(texture,true);
}