// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMainUserWidget.h"

//Start関数
void UGameMainUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//お金表示更新
void UGameMainUserWidget::UpdateMeoney(int32 money)
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
void UGameMainUserWidget::UpdateWorldTimer(int32 worldtimer)
{
	if (WorldTimerText)
	{
		WorldTimerText->SetText(FText::AsNumber(worldtimer));
	}
}

//鍬の使用・最大使用回数更新
void UGameMainUserWidget::UpdateHoeCount(int32 hoe_count, int32 max_hoe_count)
{
	if (UseHoeText)
		UseHoeText->SetText(FText::AsNumber(hoe_count));
	if (MaxHoeText)
		MaxHoeText->SetText(FText::AsNumber(max_hoe_count));
}