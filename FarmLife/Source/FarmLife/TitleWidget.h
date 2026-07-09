// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    //開始ボタン
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    //終了ボタン
    UPROPERTY(meta = (BindWidget))
    class UButton* ExitButton;

    //ガイドボタン
    UPROPERTY(meta = (BindWidget))
    class UButton* GuideButton;

    //アセット表示ボタン
    UPROPERTY(meta = (BindWidget))
    class UButton* AssetDataButton;

    //アセット名表示テキスト
    UPROPERTY(meta = (BindWidget))
    class UImage* AssetBlockTextImage;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AssetBlockText;

    //アセットボタン用テキスト
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AssetButtonText;

    //押した時のSE
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SE")
    USoundBase* click_se;

    //表示時のテキスト
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
    FText set_view_text;

    //閉じる時のテキスト
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
    FText set_close_text;

    //FPSの値
    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "FPS")
    int max_fps;


    //開始ボタンが押された時の関数
    UFUNCTION()
    void OnStartClicked();

    //終了ボタンが押された時の関数
    UFUNCTION()
    void OnExitClicked();

    //ガイドボタンが押された時の関数
    UFUNCTION()
    void OnGuideClicked();

    //アセット表示ボタンが押された時の関数
    UFUNCTION()
    void OnAssetViewClicked();

    void ExecuteTransition();//レベル遷移


private:
    FTimerHandle transition_timer;//タイマーハンドル
    float delay_timer = 0.0f;//タイマー
    FName level_name;//レベル名
    bool isView = false;//現在表示しているか
};
