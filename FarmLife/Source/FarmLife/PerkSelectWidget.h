// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ParkData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PerkSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UPerkSelectWidget : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UParkData* PerkData;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void OnClicked();

};
