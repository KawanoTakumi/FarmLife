// Fill out your copyright notice in the Description page of Project Settings.


#include "StageButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GrobalGameInstance.h"

void UStageButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//バインド
	if(Stage_Button)
		Stage_Button->OnClicked.AddDynamic(this, &UStageButtonWidget::OnClicked);
	game_instance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
}

void UStageButtonWidget::Init(UStage_DataAsset* _data)
{
	//データを取得
	Stage_Data = _data;
	//ボタンの位置を設定
	SetPosition = Stage_Data->Position;

	//ステージの番号を設定
	if (Stage_Number)
		Stage_Number->SetText(Stage_Data->Stage_Number);
	//ステージの名称を設定
	if (Stage_Name)
		Stage_Name->SetText(Stage_Data->Stage_Display_Name);
	//ステージのアイコンを設定
	if (Stage_Texture)
		Stage_Texture->SetBrushFromTexture(Stage_Data->Stage_Icon,0);

	//ステージのランク表示
	if (Stage_Rank_Image && game_instance)
	{
		switch (game_instance->g_result_rank[Stage_Data->Stage_ID])
		{
		default:
			Stage_Rank_Image->SetBrushFromTexture(RankImage[3]); break;
		case 0:
			Stage_Rank_Image->SetBrushFromTexture(RankImage[0]); break;
		case 1:
			Stage_Rank_Image->SetBrushFromTexture(RankImage[1]); break;
		case 2:
			Stage_Rank_Image->SetBrushFromTexture(RankImage[2]); break;
		case 3:
			Stage_Rank_Image->SetBrushFromTexture(RankImage[3]); break;
		}
	}

}

void UStageButtonWidget::OnClicked()
{
	//音を再生
	if (click_se)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), click_se);
		//遅延させる時間をSEの長さで設定
		delay_timer = click_se->GetDuration();
	}
	//ステージ遷移のタイマーを設定
	GetWorld()->GetTimerManager().SetTimer(timer_handle, this, &UStageButtonWidget::ExecuteTransition, delay_timer, false);
	if(game_instance)
	game_instance->g_stage_id = Stage_Data->Stage_ID;
}

void UStageButtonWidget::NativeDestruct()
{
	//初期化
	Stage_Button->OnClicked.Clear();
	Stage_Data = nullptr;

	Super::NativeDestruct();
}

//ステージ遷移関数
void UStageButtonWidget::ExecuteTransition()
{
	if (!Stage_Data)return;
	UGameplayStatics::OpenLevel(this, Stage_Data->Stage_Name);
}