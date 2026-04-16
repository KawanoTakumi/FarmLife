// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"

void USkillTreeWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void USkillTreeWidget::Init(UParkComponent* InComp)
{
    ParkComp = InComp;

    if (!RootCanvas || !NodeClass) return;

    // ノード生成
    for (int32 i = 0; i < AllParks.Num(); i++)
    {
        UParkData* Data = AllParks[i];
        if (!Data) continue;

        auto Node = CreateWidget<USkillNodeWidget>(GetWorld(), NodeClass);
        Node->Init(Data, ParkComp);

        RootCanvas->AddChild(Node);

        // とりあえず仮配置（横並び）
        if (auto CanvasSlot = Cast<UCanvasPanelSlot>(Node->Slot))
        {
            CanvasSlot->SetPosition(FVector2D(i * 150.f, 200.f));
        }

        Nodes.Add(Node);
    }

    // パーク更新時にUI更新
    if (ParkComp)
    {
        ParkComp->OnParkUpdated.AddDynamic(this, &USkillTreeWidget::RefreshAll);
    }

    RefreshAll();
}

void USkillTreeWidget::RefreshAll()
{
    for (auto Node : Nodes)
    {
        if (Node)
        {
            Node->UpdateState();
        }
    }
}