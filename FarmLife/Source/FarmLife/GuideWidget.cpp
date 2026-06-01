// Fill out your copyright notice in the Description page of Project Settings.


#include "GuideWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UGuideWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UGuideWidget::OnClickedExit);

	if (NextPageButton)
		NextPageButton->OnClicked.AddDynamic(this, &UGuideWidget::OnNextPageOpen);

	if (BackPageButton)
		BackPageButton->OnClicked.AddDynamic(this, &UGuideWidget::OnBackPageOpen);

	//最大ページを表示
	max_page = Data.Num()-1;

	if (Max_Page_Text)
		Max_Page_Text->SetText(FText::AsNumber(max_page));

	//最初のページを表示
	now_page = 0;
	if (Data.Num() > 0)
		SetData();
}

void UGuideWidget::OnClickedExit()
{
	//タイトルに戻る
	RemoveFromParent();
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void UGuideWidget::OnNextPageOpen()
{
	if (now_page < max_page)
	{
		now_page++;
		SetData();
	}
}

void UGuideWidget::OnBackPageOpen()
{
	if (now_page > 0)
	{
		now_page--;
		SetData();
	}
}

void UGuideWidget::SetData()
{
	GuideImages->SetBrushFromTexture(Data[now_page]->GuideTexture, true);
	GuideText->SetText(Data[now_page]->GuideText);
	Page_Text->SetText(FText::AsNumber(now_page));
}