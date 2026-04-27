// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "WorldTimerManageWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UWorldTimerManageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WorldTimerText;


	UFUNCTION()
	void UpdateTimer(float RemTimer);
};
