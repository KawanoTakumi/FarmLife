// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Stage_DataAsset.h"
#include "StageSelectWidget.h"
#include "StageButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UStageButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct()override;

	void NativeDestruct()override;

public:
	void Init(UStage_DataAsset* _data);

	//親ウィジェット
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UStageSelectWidget* StageSelectWidget;

	//配置位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Position")
	FVector2D SetPosition;

	//ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* Stage_Button;

	//ステージ名
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Stage_Name;

	//ステージの番号
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Stage_Number;

	//ステージアイコン
	UPROPERTY(meta = (BindWidget))
	UImage* Stage_Texture;

	//ステージデータ
	UPROPERTY()
	UStage_DataAsset* Stage_Data;

	
	UFUNCTION()
	void OnClicked();


};