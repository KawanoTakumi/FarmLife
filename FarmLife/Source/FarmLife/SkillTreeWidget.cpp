// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"
#include "PlayerCharacter.h"

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
    //パークコンポーネントを探す
    APlayerCharacter* Chara = Cast<APlayerCharacter>(GetOwningPlayerPawn());
    if (Chara)
    {
        ParkComp = Chara->FindComponentByClass<UParkComponent>();
    }

    //パークコンポーネントを取得できたらInit関数で情報を渡す
    if (ParkComp)
    {
        Init(ParkComp);
    }
}

void USkillTreeWidget::Init(UParkComponent* InComp)
{
    ParkComp = InComp;
    if (!RootCanvas || !NodeClass) return;
    if (AllParks.Num() >= 1)
    {
        // ノード生成
        for (int32 i = 0; i < AllParks.Num(); i++)
        {
            UParkData* Data = AllParks[i];
            if (!Data) continue;
            auto Node = CreateWidget<USkillNodeWidget>(GetWorld(), NodeClass);
            Node->Init(Data, ParkComp);
            Node->SkillTree = this;

            RootCanvas->AddChild(Node);

            //配置（X、Y）
            if (auto CanvasSlot = Cast<UCanvasPanelSlot>(Node->Slot))
            {
                CanvasSlot->SetPosition(FVector2D(Node->SetPosition.X * 150.0f,Node->SetPosition.Y * 150.0f));
            }

            Nodes.Add(Node);
        }

    }

    // パーク更新時にUI更新
    if (ParkComp)
    {
        ParkComp->OnParkUpdated.AddDynamic(this, &USkillTreeWidget::RefreshAll);
    }
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