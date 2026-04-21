// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "SkillNodeWidget.h"
#include "ParkComponent.h"
#include "ParkData.h"
#include "SkillTreeWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosed);
/**
 * 
 */
UCLASS()
class FARMLIFE_API USkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void Init(UParkComponent* InComp);

    UPROPERTY(BlueprintAssignable)
    FOnClosed OnClosed;

    //パークの説明
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PerkDesc;
    
    //パークの名称
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PerkName;

protected:
    virtual void NativeConstruct() override;


    //戻るボタン
    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;

    // Canvas（配置用）
    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* RootCanvas;

    // ノードのクラス（BP指定）
    UPROPERTY(EditAnywhere, Category = "SkillTree")
    TSubclassOf<USkillNodeWidget> NodeClass;

    // 全パーク
    UPROPERTY(EditAnywhere, Category = "SkillTree")
    TArray<UParkData*> AllParks;

    // コンポーネント
    UPROPERTY()
    UParkComponent* ParkComp;

    // 生成したノード
    UPROPERTY()
    TArray<USkillNodeWidget*> Nodes;


    // 更新
    UFUNCTION()
    void RefreshAll();

    //UIからゲームに戻る
    UFUNCTION()
    void ExitUI();

public:
    //UI作成
    UFUNCTION()
    void CreateWidgetData();
};