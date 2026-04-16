// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParkData.h"
#include "PerkSelectWidget.h"
#include "Components/ListView.h"
#include "ParkUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMLIFE_API UParkUIWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetUp(TArray<UParkData*> park);

	//リストビュー、今回は使わない
	UPROPERTY(meta = (BindWidget))
	UListView* ParkListView;

	

};
