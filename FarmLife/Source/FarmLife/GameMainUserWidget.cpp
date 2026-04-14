// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMainUserWidget.h"

//‚¨‹à•\Ž¦XV
void UGameMainUserWidget::UpdateMeoney(int32 money)
{
	if (MoneyText)
	{
		MoneyText->SetText(FText::AsNumber(money));
	}
}