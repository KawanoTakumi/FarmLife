// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
    class UTextBlock* Result_Time_Text;

    //スコア::採取回数
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Result_UseCount_Text;

    //スコア::ランク
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Rank_Text;

    //タイトル移動
    UFUNCTION()
    void OnStartClicked();

protected:
    virtual void NativeConstruct() override;

    //ランクを算出（time）
    void SetResultRank(int time,bool isWin);

private:
    int32 max_timer;
    int32 resuslt_timer;
};