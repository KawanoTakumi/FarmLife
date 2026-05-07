// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StageSelect_Widget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UStageSelect_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	//戻るボタン
	UPROPERTY(meta = (BindWidget))
	UButton* Button_back;

	//ステージセレクト
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Stage_1;

	//クリック時の挙動
	UFUNCTION()
	void OnClicked_Back();

	UFUNCTION()
	void OnClicked_Stage1();

	protected:
    virtual void NativeConstruct() override;

};