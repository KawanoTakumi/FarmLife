// Fill out your copyright notice in the Description page of Project Settings.


#include "PerkSelectWidget.h"

void UPerkSelectWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	PerkData = Cast<UParkData>(ListItemObject);

	if (PerkData && NameText)
	{
		NameText->SetText(FText::FromName(PerkData->ParkName));
	}

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &UPerkSelectWidget::OnClicked);
	}

}

void UPerkSelectWidget::OnClicked()
{
	if (!PerkData) return;
	else
	{
		//ƒCƒxƒ“ƒg”­‰Î
		OnPerkClick.Broadcast(PerkData);
	}
}