// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "GrobalGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UResultWidget::OnStartClicked);
	}

	//gameInstanceから経過時間を取得
	g_gameInstance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
	if (g_gameInstance)
	{
		result_timer = g_gameInstance->g_timer;//残り時間
		max_timer = g_gameInstance->g_max_timer;//最大時間
		use_count = g_gameInstance->g_use_count;//採取回数

		//最大時間から残り時間を差し引いて経過時間を取得
		int calc_timer = max_timer - result_timer;

		calc_min = calc_timer / 60;//分を算出
		calc_sec = calc_timer - (calc_min * 60);//秒を算出
	}
	//リザルトの時間テキスト更新
	if (Result_Time_Text_Min)
		Result_Time_Text_Min->SetText(FText::AsNumber(calc_min));
	if (Result_Time_Text_Second)
		Result_Time_Text_Second->SetText(FText::AsNumber(calc_sec));

	//リザルトの採取回数テキストを更新
	if (Result_UseCount_Text)
		Result_UseCount_Text->SetText(FText::AsNumber(use_count));

	SetResultRank(result_timer,g_gameInstance->isWin);
}

//スタートを押された時
void UResultWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void UResultWidget::SetResultRank(int time ,bool isWin)
{
	int calc_time = max_timer - time;
	//負けの時
	if (!isWin)
	{
		//強制的にランクをCに設定する
		Rank_Image->SetBrushFromTexture(Rank_Images[1],true);
		SetResultStageValue(1);
		return;
	}
	//勝ちの時
	if (calc_time <= (max_timer / 10) * 3)
	{
		Rank_Image->SetBrushFromTexture(Rank_Images[4], true);
		SetResultStageValue(4);
	}
	else if (calc_time <= (max_timer / 10) * 6)
	{
		Rank_Image->SetBrushFromTexture(Rank_Images[3], true);
		SetResultStageValue(3);
	}
	else if (calc_time <= (max_timer / 10) * 8)
	{
		Rank_Image->SetBrushFromTexture(Rank_Images[2], true);
		SetResultStageValue(2);
	}
	else
	{
		Rank_Image->SetBrushFromTexture(Rank_Images[1], true);
		SetResultStageValue(1);
	}
}

void UResultWidget::SetResultStageValue(int value)
{
	if(g_gameInstance->g_result_rank[g_gameInstance->g_stage_id] < value)
		g_gameInstance->g_result_rank[g_gameInstance->g_stage_id] = value;
}