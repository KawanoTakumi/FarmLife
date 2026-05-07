// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelect_Widget.h"
#include "Kismet/GameplayStatics.h"

void UStageSelect_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_back)
		Button_back->OnClicked.AddDynamic(this, &UStageSelect_Widget::OnClicked_Back);

	if (Button_Stage_1)
		Button_Stage_1->OnClicked.AddDynamic(this, &UStageSelect_Widget::OnClicked_Stage1);

}

void UStageSelect_Widget::OnClicked_Back()
{
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void UStageSelect_Widget::OnClicked_Stage1()
{
	UGameplayStatics::OpenLevel(this, FName("Stage_1"));
}
