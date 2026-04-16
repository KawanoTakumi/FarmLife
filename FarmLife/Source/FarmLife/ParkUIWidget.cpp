// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkUIWidget.h"

void UParkUIWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UParkUIWidget::SetUo(const TArray<UParkData*> data)
{
	ParkListView->ClearListItems();

	for (auto* Park : data)
	{
		ParkListView->AddItem(Park);
	}
}

