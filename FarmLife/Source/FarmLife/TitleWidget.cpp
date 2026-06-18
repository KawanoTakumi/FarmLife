// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
        StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
    if (ExitButton)
        ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
    if (GuideButton)
        GuideButton->OnClicked.AddDynamic(this, &UTitleWidget::OnGuideClicked);

}

void UTitleWidget::OnStartClicked()
{
    //ステージ選択へ
    if (click_se)
        UGameplayStatics::PlaySound2D(GetWorld(), click_se);
    RemoveFromParent();
    UGameplayStatics::OpenLevel(this, FName("Stage_Select"));
}

void UTitleWidget::OnExitClicked()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (click_se)
        UGameplayStatics::PlaySound2D(GetWorld(), click_se);
    //ゲーム終了
    if(PC)
    UKismetSystemLibrary::QuitGame(this,nullptr, EQuitPreference::Quit, false);
}

void UTitleWidget::OnGuideClicked()
{
    //ガイド画面へ
    if (click_se)
        UGameplayStatics::PlaySound2D(GetWorld(), click_se);
    RemoveFromParent();
    UGameplayStatics::OpenLevel(this, FName("Guide"));
}