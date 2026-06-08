// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "StageSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UStageSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootCanvas;

	//ノードクラス
	UPROPERTY(EditAnywhere, Category = "Node")
	TSubclassOf<class UStageButtonWidget> StageNodeWidget;

	//ステージデータ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node")
	TArray<class UStage_DataAsset*> AllStages;

	//生成したノード
	UPROPERTY()
	TArray<UStageButtonWidget*> Nodes;

	//戻る
	UFUNCTION()
	void Back();

	//UI作成
	UFUNCTION()
	void Init();
};