// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParkData.h"
#include "ParkComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SkillNodeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API USkillNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(UParkData* InData, UParkComponent* InComp);

	UFUNCTION(BlueprintCallable)
	void UpdateState();

    UPROPERTY(EditAnywhere,BluePrintReadWrite)
    class USkillTreeWidget* SkillTree;

protected:
    virtual void NativeConstruct() override;

    virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MyEvent) override;

    // ボタン
    UPROPERTY(meta = (BindWidget))
    UButton* NodeButton;

    // アイコン（任意）
    UPROPERTY(meta = (BindWidgetOptional))
    UImage* Icon;

    // 名前表示（任意）
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* NameText;


    // データ
    UPROPERTY()
    UParkData* ParkData;

    UPROPERTY()
    UParkComponent* ParkComp;

    // クリック処理
    UFUNCTION()
    void OnClicked();
};
