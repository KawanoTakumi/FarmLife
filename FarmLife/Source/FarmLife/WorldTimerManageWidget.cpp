// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTimerManageWidget.h"

//タイマー表示更新
void UWorldTimerManageWidget::UpdateTimer(float RemTimer)
{
	if (WorldTimerText)
	{
		WorldTimerText->SetText(FText::AsNumber(FMath::Max(0, FMath::FloorToInt(RemTimer))));
	}

}