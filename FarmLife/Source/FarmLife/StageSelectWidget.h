// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* St1Button;
	UPROPERTY(meta = (BindWidget))
	UButton* St2Button;
	UPROPERTY(meta = (BindWidget))
	UButton* St3Button;

	UFUNCTION()
	void Back();

	UFUNCTION()
	void Stage1();

	UFUNCTION()
	void Stage2(); 

	UFUNCTION()
	void Stage3();
};