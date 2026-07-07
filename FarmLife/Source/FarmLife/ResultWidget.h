// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UResultWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    //タイトルに戻るボタン
    UPROPERTY(meta = (BindWidget))
    class UButton* TitleButton;

    //スコア::時間
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Result_Time_Text_Min;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Result_Time_Text_Second;

    //ランク設定の分表示
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_S_Timer_Text_Min;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_A_Timer_Text_Min;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_B_Timer_Text_Min;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_C_Timer_Text_Min;

    //ランク設定の秒表示
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_S_Timer_Text_Second;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_A_Timer_Text_Second;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_B_Timer_Text_Second;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_C_Timer_Text_Second;


    //スコア::採取回数
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Result_UseCount_Text;

    //スコア::ランク
    UPROPERTY(meta = (BindWidget))
    class UImage* Rank_Image;

    //タイトル移動
    UFUNCTION()
    void OnStartClicked();

protected:
    virtual void NativeConstruct() override;

    //ランクを算出（time）
    void SetResultRank(int time, bool isWin);
    //ランクをグローバル変数に入れ、保存する
    void SetResultStageValue(int value);
    //ランク計測用関数
    void Calc_Timer(UTextBlock* Min_text,UTextBlock* Sec_text,int timer);
    //ランク用テクスチャ
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Image")
    TArray<UTexture2D*> Rank_Images;


private:
    int32 max_timer;
    int32 result_timer;
    int32 calc_min;
    int32 calc_sec;
    int32 use_count;
    class UGrobalGameInstance* g_gameInstance;

    int rank_s_timer = 0;
    int rank_a_timer = 0;
    int rank_b_timer = 0;
    int rank_c_timer = 0;

};