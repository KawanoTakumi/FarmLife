// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"
/**
 * 
 */
UCLASS()
class FARMLIFE_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


	//ゲームに戻る
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	//タイトルに戻る
	UPROPERTY(meta = (BindWidget))
	UButton* TitleButton;

	UFUNCTION()
	void OnClickedBack();

	UFUNCTION()
	void OnClickedTitle();

private:
	virtual void NativeConstruct() override;

};
