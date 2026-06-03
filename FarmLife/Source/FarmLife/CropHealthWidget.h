// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CropHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UCropHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;


public:
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	void UpdateHealthBar(int now_hp,int max_hp);
};
