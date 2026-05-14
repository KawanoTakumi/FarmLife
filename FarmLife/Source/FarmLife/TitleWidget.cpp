// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
        ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
    }
}

void UTitleWidget::OnStartClicked()
{
    //ステージ選択へ
    RemoveFromParent();
    UGameplayStatics::OpenLevel(this, FName("Stage_1"));
}

void UTitleWidget::OnExitClicked()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

    //ゲーム終了
    if(PC)
    UKismetSystemLibrary::QuitGame(this,nullptr, EQuitPreference::Quit, false);
}