// Fill out your copyright notice in the Description page of Project Settings.


#include "StageNodeWidget.h"
#include "Kismet/GameplayStatics.h"

void UStageNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//ƒoƒCƒ“ƒh
	//if (StageSelectButton)
	//	StageSelectButton->OnClicked.AddDynamic(this, &UStageNodeWidget::OnClicked);
}

void UStageNodeWidget::Init(FName name,UTexture2D* image,FText level_name)
{
	//stage_name = name;
	//StageIcon->SetBrushFromTexture(image);
	//StageName->SetText(level_name);
}

void UStageNodeWidget::OnClicked()
{
	//if (StageSelectButton)
	//{
	//	StageSelectButton->SetIsEnabled(false);
	//}

	//RemoveFromParent();
	//UGameplayStatics::OpenLevel(this, stage_name);
}

void UStageNodeWidget::NativeDestruct()
{
	if (StageSelectButton)
	{
		//StageSelectButton->OnClicked.RemoveDynamic(this, &UStageNodeWidget::OnClicked);
	}

	Super::NativeDestruct();
}