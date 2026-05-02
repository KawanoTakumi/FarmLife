// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Blueprint/UserWidget.h"


void ATitleGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (TitleWidgetClass)
    {
        UUserWidget* Widget = CreateWidget(GetWorld(), TitleWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
        }
    }

    // UI‘€ì—p‚É‚·‚é
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->bShowMouseCursor = true;

        FInputModeUIOnly InputMode;
        PC->SetInputMode(InputMode);
    }
}