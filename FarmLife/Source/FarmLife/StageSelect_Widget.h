// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "StageNodeWidget.h"
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

	//移動したいレベルのリスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "name")
	TArray<UWorld*> Stage_Levels;

	//レベル毎のステージ画像
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "image")
	TArray<UTexture2D*> Stage_Images;

	//レベル毎のステージ名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "name")
	TArray<FText> Stage_Names;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "position")
	FVector2D StartPos;

	// Canvas（配置用）
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "position")
	int Range = 0;

	// 生成したノード
	UPROPERTY()
	TArray<UStageNodeWidget*> Nodes;

	// ノードのクラス（BP指定）
	UPROPERTY(EditAnywhere, Category = "SkillTree")
	TSubclassOf<UStageNodeWidget> NodeClass;

	//クリック時の挙動
	UFUNCTION()
	void OnClicked_Back();

	UFUNCTION()
	void Init();

	void CleanUp();
protected:
    virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};