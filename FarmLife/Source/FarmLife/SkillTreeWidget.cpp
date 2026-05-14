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
    //フォーカス設定
    SetIsFocusable(true);

    if (APlayerController* PC = GetOwningPlayer())
    {
        FInputModeUIOnly Mode;
        Mode.SetWidgetToFocus(TakeWidget());
        PC->SetInputMode(Mode);
        PC->bShowMouseCursor = true;
    }


    ParkComp = InComp;
    if (!RootCanvas || !NodeClass) return;
    if (AllParks.Num() >= 1)
    {
        // ノード生成
        for (int32 i = 0; i < AllParks.Num(); i++)
        {
            AllParks[i]->bCan = false;
            AllParks[i]->bOwned = false;
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
            if (AllParks[count]->bCan == false && AllParks[count]->bOwned == false)
            {
                count++;
                continue;
            }
            //現在のポイント取得
            FVector2D start_vec = { 
                StartPerkPosX + 50 + AllParks[count]->PositionGrid.X * PerkRange,
                StartPerkPosY + 50 + AllParks[count]->PositionGrid.Y * PerkRange
            };

            //要求パーク毎の終点を求める
            for (int req_perk = 0; req_perk < AllParks[count]->RequiredPerk.Num(); req_perk++)
            {
                FVector2D end_vec = {
                StartPerkPosX + 50 + AllParks[count]->RequiredPerk[req_perk]->PositionGrid.X * PerkRange,
                StartPerkPosY + 50 + AllParks[count]->RequiredPerk[req_perk]->PositionGrid.Y * PerkRange
                };
                FLinearColor linear_color;
                if (AllParks[count]->bOwned)
                    linear_color = FLinearColor::Yellow;
                else if (AllParks[count]->bCan)
                    linear_color = FLinearColor::Green;
                //線を描画する為の線の座標を設定
                TArray<FVector2D> draw_line_pos = { start_vec,end_vec };

                FSlateDrawElement::MakeLines(
                    OutDrawElements,
                    MaxLayerID -60,
                    AllottedGeometry.ToPaintGeometry(),
                    draw_line_pos,
                    ESlateDrawEffect::None,
                    linear_color);
            }
        }
    }
    return MaxLayerID + 1;
}

FReply USkillTreeWidget::NativeOnKeyDown(const FGeometry& InGeometry,
    const FKeyEvent& KeyEvent)
{
    FKey PressedKey = KeyEvent.GetKey();
    FVector2D MovementDelta = FVector2D::ZeroVector;

    if (PressedKey == EKeys::W)MovementDelta.Y -= 30.0f;
    if (PressedKey == EKeys::S)MovementDelta.Y += 30.0f;
    if (PressedKey == EKeys::A)MovementDelta.X -= 30.0f;
    if (PressedKey == EKeys::D)MovementDelta.X += 30.0f;
    
    for (int i = 0; i < Nodes.Num(); i++)
    {
        if (!MovementDelta.IsZero())
        {
            UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Nodes[i]->Slot);
            if (CanvasSlot)
            {
                UE_LOG(LogTemp, Warning, TEXT("Moveing"));
                FVector2D current_pos = CanvasSlot->GetPosition();
                CanvasSlot->SetPosition(current_pos + MovementDelta);
            }
        }

        if (i >= Nodes.Num())
        {
            UE_LOG(LogTemp, Warning, TEXT("Finish"));
            return FReply::Handled();
        }
    }
    return Super::NativeOnKeyDown(InGeometry, KeyEvent);
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