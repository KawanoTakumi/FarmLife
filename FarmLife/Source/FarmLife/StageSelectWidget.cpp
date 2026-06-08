// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "StageButtonWidget.h"
#include "Stage_DataAsset.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //仮のステージ移行スクリプト
    //後に動的生成に切り替える

    BackButton->OnClicked.AddDynamic(this, &UStageSelectWidget::Back);
    //St1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage1);
    //St2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage2);
    //St3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::Stage3);

    Init();
}

//ノード作成
void UStageSelectWidget::CreateWidgetUI()
{
    //Init();
}

void UStageSelectWidget::Init()
{
    if (AllStages.Num() >= 1)
    {
        //ノード作成
        for (int32 i = 0; i < AllStages.Num(); i++)
        {
            UStage_DataAsset* Data = AllStages[i];
            if (!Data)continue;
            auto Node = CreateWidget<UStageButtonWidget>(GetWorld(),StageNodeWidget);
            Node->Init(Data);
            Node->StageSelectWidget = this;
            RootCanvas->AddChild(Node);

            //配置
            if (auto CanvasSlot = Cast<UCanvasPanelSlot>(Node->Slot))
            {
                CanvasSlot->SetPosition(FVector2D(
                    Node->SetPosition.X,
                    Node->SetPosition.Y
                ));
            }

            Nodes.Add(Node);
        }
    }
}

void UStageSelectWidget::NativeDestruct()
{
    //初期化
    for (auto Node : Nodes)
    {
        if (Node)
            Node->RemoveFromParent();
    }
    Nodes.Empty();


    Super::NativeDestruct();
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

    UGameplayStatics::OpenLevel(this, FName("Stage_3"));

}