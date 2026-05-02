// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
    }
}

void UTitleWidget::OnStartClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainMap"));
}