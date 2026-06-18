// Fill out your copyright notice in the Description page of Project Settings.


#include "StageButtonWidget.h"
#include "Kismet/GameplayStatics.h"

void UStageButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//ƒoƒCƒ“ƒh
	if(Stage_Button)
		Stage_Button->OnClicked.AddDynamic(this, &UStageButtonWidget::OnClicked);
}

void UStageButtonWidget::Init(UStage_DataAsset* _data)
{
	Stage_Data = _data;
	SetPosition = Stage_Data->Position;
	if (Stage_Number)
		Stage_Number->SetText(Stage_Data->Stage_Number);
	if (Stage_Name)
		Stage_Name->SetText(Stage_Data->Stage_Display_Name);
	if (Stage_Texture)
		Stage_Texture->SetBrushFromTexture(Stage_Data->Stage_Icon,0);
}

void UStageButtonWidget::OnClicked()
{
	if (!Stage_Data)return;
	UGameplayStatics::OpenLevel(this,Stage_Data->Stage_Name);
}

void UStageButtonWidget::NativeDestruct()
{
	Stage_Button->OnClicked.Clear();
	Stage_Data = nullptr;

	Super::NativeDestruct();
}