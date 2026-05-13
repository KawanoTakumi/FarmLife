// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "StageNodeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UStageNodeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//ボタン
	UPROPERTY(meta = (BindWidget))
	UButton* StageSelectButton;

	//画像
	UPROPERTY(meta = (BindWidget))
	UImage* StageIcon;

	//ステージ名
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StageName;

	//データのワールド名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "name")
	FName stage_name;

	UFUNCTION()
	void OnClicked();

	void Init(FName name,UTexture2D* image,FText stage_name);

protected:
	virtual void NativeConstruct() override;

};
