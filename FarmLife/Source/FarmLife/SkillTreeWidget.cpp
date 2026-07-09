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
    if (push_se)
        UGameplayStatics::PlaySound2D(GetWorld(), push_se);

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;
    if (ParkComp)
    {
        ParkComp->OnParkUpdated.RemoveDynamic(this, &USkillTreeWidget::RefreshAll);
    }
    for (auto Node : Nodes)
    {
        if (Node)
        {
            Node->RemoveFromParent();
        }
    }
    Nodes.Empty();
    // UI削除
    Cleanup();
    RemoveFromParent();

    ParkComp = nullptr;
    // 入力をゲームに戻す
    PC->bShowMouseCursor = false;

    FInputModeGameOnly Mode;
    PC->SetInputMode(Mode);
    PC->SetIgnoreMoveInput(false);
    OnClosed.Broadcast();

    AActor* FoundTimer =
        UGameplayStatics::GetActorOfClass(GetWorld(), AWorldTimerActor::StaticClass());
    AWorldTimerActor* worldTimer = Cast<AWorldTimerActor>(FoundTimer);

    if (worldTimer)
        worldTimer->UnPauseTimer();


}

void USkillTreeWidget::NativeDestruct()
{
    if (ParkComp)
        ParkComp->OnParkUpdated.RemoveDynamic(this, &USkillTreeWidget::RefreshAll);


    for (auto Node : Nodes)
    {
        if (Node)
            Node->RemoveFromParent();
    }

    Nodes.Empty();
    ParkComp = nullptr;

    Super::NativeDestruct();
}

void USkillTreeWidget::Cleanup()
{
    if (ParkComp)
    {
        ParkComp->OnParkUpdated.RemoveDynamic(this, &USkillTreeWidget::RefreshAll);
    }

    for (auto Node : Nodes)
    {
        if (Node)
        {
            Node->RemoveFromParent();
            Node->ConditionalBeginDestroy(); // ←重要
        }
    }

    Nodes.Empty();
    ParkComp = nullptr;
}