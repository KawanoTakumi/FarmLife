// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeWidget.h"
#include "PlayerCharacter.h"
#include "WorldTimerActor.h"

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
                CanvasSlot->SetPosition(FVector2D(
                    StartPerkPosX + Node->SetPosition.X *PerkRange, 
                    StartPerkPosY+Node->SetPosition.Y * PerkRange));

                //要求ノードがある場合、その座標までラインを引く

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

int32 USkillTreeWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
    int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    int32 MaxLayerID = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    //ここでPerk間の線を描画する
    if (AllParks.Num() != 0)
    {
        for (int count = 0; count < AllParks.Num(); count++)
        {
            //現在のポイント取得
            FVector2D start_vec = AllParks[count]->PositionGrid;

            //要求パーク毎の終点を求める
            for (int req_perk = 0; req_perk < AllParks[count]->RequiredPerk.Num(); req_perk++)
            {
                FVector2D end_vec = AllParks[count]->RequiredPerk[req_perk]->PositionGrid;

                //線を描画する為の線の座標を設定
                TArray<FVector2D> draw_line_pos = { start_vec,end_vec };

                FSlateDrawElement::MakeLines(
                    OutDrawElements,
                    MaxLayerID + 1,
                    AllottedGeometry.ToPaintGeometry(),
                    draw_line_pos,
                    ESlateDrawEffect::None,
                    FLinearColor::White);

                //初期化
                draw_line_pos.Empty();
            }
        }
    }
    return MaxLayerID+1;
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