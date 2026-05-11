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
		resuslt_timer = g_gameinstance->g_timer;
		max_timer = g_gameinstance->g_max_timer;
	}
	//リザルトの時間更新
	if (Result_Time_Text)
		Result_Time_Text->SetText(FText::AsNumber(max_timer - resuslt_timer));


	SetResultRank(resuslt_timer,g_gameinstance->isWin);
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

	//仮のランク設定(制限時間を10分割して、その割合から計測)
	if ((max_timer / 10) * 2 >= calc_time)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("C"));
	}
	else if ((max_timer / 10) * 4 >= calc_time)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("B"));
	}
	else if ((max_timer / 10) * 6 >= calc_time)
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("A"));
	}
	else
	{
		if (Rank_Text)
			Rank_Text->SetText(FText::FromString("S"));
	}
}