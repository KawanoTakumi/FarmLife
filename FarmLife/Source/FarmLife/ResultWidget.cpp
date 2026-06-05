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
	UGrobalGameInstance* g_gameInstance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
	if (g_gameInstance)
	{
		result_timer = g_gameInstance->g_timer;
		max_timer = g_gameInstance->g_max_timer;
		use_count = g_gameInstance->g_use_count;
		int calc_timer = max_timer - result_timer;
		calc_min = calc_timer / 60;
		calc_sec = calc_timer - (calc_min * 60);
	}
	//リザルトの時間更新
	if (Result_Time_Text_Min)
		Result_Time_Text_Min->SetText(FText::AsNumber(calc_min));
	if (Result_Time_Text_Second)
		Result_Time_Text_Second->SetText(FText::AsNumber(calc_sec));

	//リザルトの採取回数を更新
	if (Result_UseCount_Text)
		Result_UseCount_Text->SetText(FText::AsNumber(use_count));

	SetResultRank(result_timer,g_gameInstance->isWin);
}

void UResultWidget::OnStartClicked()
{
	//タイトルへ
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void UResultWidget::SetResultRank(int time ,bool isWin)
{
	int calc_time = max_timer - time;

	if (!Rank_Text)return;
	//負けの時
	if (!isWin)
	{
			Rank_Text->SetText(FText::FromString("C"));
		return;
	}
	//勝ちの時
	if (calc_time <= (max_timer / 10) * 3)
	{
		Rank_Text->SetText(FText::FromString("S"));
	}
	else if (calc_time <= (max_timer / 10) * 5)
	{
		Rank_Text->SetText(FText::FromString("A"));
	}
	else if (calc_time <= (max_timer / 10) * 6)
	{
		Rank_Text->SetText(FText::FromString("B"));
	}
	else
	{
		Rank_Text->SetText(FText::FromString("C"));
	}
}