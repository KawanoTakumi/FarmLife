// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelect_Widget.h"
#include "Kismet/GameplayStatics.h"

void UStageSelect_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_back)
		Button_back->OnClicked.AddDynamic(this, &UStageSelect_Widget::OnClicked_Back);

	Init();
}

void UStageSelect_Widget::Init()
{
	if (Stage_Levels.Num() <= 0)return;

	for (int16 i = 0; i < Stage_Levels.Num(); i++)
	{
		auto Node = CreateWidget<UStageNodeWidget>(GetWorld(), NodeClass);
		Node->Init(Stage_Levels[i]->GetFName(),Stage_Images[i],Stage_Names[i]);
		RootCanvas->AddChild(Node);

		//配置（X、Y）
		if (auto CanvasSlot = Cast<UCanvasPanelSlot>(Node->Slot))
		{
			CanvasSlot->SetPosition(FVector2D(
				StartPos.X + i * Range,
				StartPos.Y));
		}

		Nodes.Add(Node);
	}
}

void UStageSelect_Widget::OnClicked_Back()
{
	UGameplayStatics::OpenLevel(this, FName("Title"));
}
