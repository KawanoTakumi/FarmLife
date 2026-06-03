// Fill out your copyright notice in the Description page of Project Settings.


#include "CropHealthWidget.h"


void UCropHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();



}

void UCropHealthWidget::UpdateHealthBar(int now_hp,int max_hp)
{
	if (HealthBar && max_hp > 0)
	{
		HealthBar->SetPercent(now_hp/max_hp);
	}
}