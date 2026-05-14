// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //仮のステージ移行スクリプト
    //後に動的生成に切り替える

    BackButton->OnClicked.AddDynamic(this, &UStageSelectWidget::Back);
    St1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage1);
    St2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage2);
    St3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage3);

}
void UStageSelectWidget::Back()
{
    RemoveFromParent();

    UGameplayStatics::OpenLevel(this, FName("Title"));

}
void UStageSelectWidget::Stage1()
{
    RemoveFromParent();

    UGameplayStatics::OpenLevel(this, FName("Stage_1"));

}
void UStageSelectWidget::Stage2()
{
    RemoveFromParent();

    UGameplayStatics::OpenLevel(this, FName("Stage_2"));

}
void UStageSelectWidget::Stage3()
{
    RemoveFromParent();

    UGameplayStatics::OpenLevel(this, FName("Stage_1"));

}