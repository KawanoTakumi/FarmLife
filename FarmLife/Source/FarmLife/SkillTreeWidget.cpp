// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"

void USkillTreeWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &USkillTreeWidget::ExitUI);
    }
}

void USkillTreeWidget::CreateWidgetData()
{
    UE_LOG(LogTemp, Warning, TEXT("park aveirable %d"), AllParks.Num());
    if (ParkComp)
        Init(ParkComp);
   
}

void USkillTreeWidget::Init(UParkComponent* InComp)
{
    UE_LOG(LogTemp, Warning, TEXT("park aveirable %d"), AllParks.Num());
    if (!RootCanvas || !NodeClass) return;
    if (AllParks.Num() >= 1)
    {
        // ノード生成
        for (int32 i = 0; i < AllParks.Num(); i++)
        {
            UParkData* Data = AllParks[i];
            if (!Data) continue;
            auto Node = CreateWidget<USkillNodeWidget>(GetWorld(), NodeClass);
            Node->Init(Data, InComp);

            RootCanvas->AddChild(Node);

            // とりあえず仮配置（横並び）
            if (auto CanvasSlot = Cast<UCanvasPanelSlot>(Node->Slot))
            {
                CanvasSlot->SetPosition(FVector2D(i * 150.f, 200.f));
            }

            Nodes.Add(Node);
        }

    }

    // パーク更新時にUI更新
    if (InComp)
    {
        InComp->OnParkUpdated.AddDynamic(this, &USkillTreeWidget::RefreshAll);
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

void USkillTreeWidget::ExitUI()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    // UI削除
    RemoveFromParent();
    // 入力をゲームに戻す
    PC->bShowMouseCursor = false;

    FInputModeGameOnly Mode;
    PC->SetInputMode(Mode);
    PC->SetIgnoreMoveInput(false);
    OnClosed.Broadcast();

}