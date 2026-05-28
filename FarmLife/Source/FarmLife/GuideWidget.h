// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GuideDataAsset.h"
#include "GuideWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UGuideWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

public:
	//戻るボタン
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	//現在のページ数
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Page_Text;

	//最大ページ数
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Max_Page_Text;

	//ページを進める
	UPROPERTY(meta = (BindWidget))
	class UButton* NextPageButton;

	//ページを戻る
	UPROPERTY(meta = (BindWidget))
	class UButton* BackPageButton;

	//描画画像
	UPROPERTY(meta = (BindWidget))
	class UImage* GuideImages;

	//説明テキスト
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GuideText;

	UFUNCTION()
	void OnClickedExit();

	UFUNCTION()
	void OnNextPageOpen();

	UFUNCTION()
	void OnBackPageOpen();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<UGuideDataAsset*> Data;

private:
	int8 now_page = 0;//現在のページ

	void SetData();

};