// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "StageButtonWidget.h"
#include "Stage_DataAsset.h"
#include "GrobalGameInstance.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    BackButton->OnClicked.AddDynamic(this, &UStageSelectWidget::Back);

    UGrobalGameInstance* game_instance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
    
    if (game_instance->g_result_rank.Num() < 1)
    {
        for (int i = 0; i < 4; i++)
            game_instance->g_result_rank.Add(0);
    }
    Init();
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