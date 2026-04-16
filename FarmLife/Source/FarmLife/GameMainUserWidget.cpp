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