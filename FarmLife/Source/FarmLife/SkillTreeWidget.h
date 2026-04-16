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

/**
 * 
 */
UCLASS()
class FARMLIFE_API USkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void Init(UParkComponent* InComp);

protected:
    virtual void NativeConstruct() override;

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

};
