// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GrobalGameInstance.h"
#include "Kismet/GameplayStatics.h"
void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UResultWidget::OnStartClicked);
	}

	//gameInstanceから経過時間を取得
	UGrobalGameInstance* g_gameinstance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
	if (g_gameinstance)
	{
		result_timer = g_gameinstance->g_timer;
		max_timer = g_gameinstance->g_max_timer;
		int calc_timer = max_timer - result_timer;
		calc_min = calc_timer / 60;
		calc_sec = calc_timer - (calc_min * 60);
	}
	//リザルトの時間更新
	if (Result_Time_Text_Min)
		Result_Time_Text_Min->SetText(FText::AsNumber(calc_min));
	if (Result_Time_Text_Second)
		Result_Time_Text_Second->SetText(FText::AsNumber(calc_sec));


	SetResultRank(result_timer,g_gameinstance->isWin);
}

void UResultWidget::OnStartClicked()
{
	//タイトルへ
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void UResultWidget::SetResultRank(int time ,bool isWin)
{
	int calc_time = max_timer - time;

	if (!isWin)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("C"));
		return;
	}
	if (calc_time >= (max_timer / 10) * 6)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("S"));
	}
	else if (calc_time >= (max_timer / 10) * 5)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("A"));
	}
	else if (calc_time >= (max_timer / 10) * 3)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("B"));
	}
	else
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("C"));
	}
}