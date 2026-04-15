// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SpawnField.h"
#include "GameMainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UGameMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoneyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(EditAnywhere)
	ASpawnField* SpawnField;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateMeoney(int32 money);

};