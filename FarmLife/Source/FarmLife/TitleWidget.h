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
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* ExitButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* GuideButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SE")
    USoundBase* click_se;

    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnExitClicked();

    UFUNCTION()
    void OnGuideClicked();

    void ExecuteTransition();//レベル遷移
private:
    FTimerHandle transition_timer;//タイマーハンドル
    float delay_timer = 0.0f;//タイマー
    FName level_name;
};
