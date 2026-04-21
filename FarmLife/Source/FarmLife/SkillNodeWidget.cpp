// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodeWidget.h"
#include "SkillTreeWidget.h"
void USkillNodeWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (NodeButton)
    {
        NodeButton->OnClicked.AddDynamic(this, &USkillNodeWidget::OnClicked);
    }
}
//カーソルが上に乗った時を検知
void USkillNodeWidget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MyPointer)
{
    Super::NativeOnMouseEnter(MyGeometry, MyPointer);
    UE_LOG(LogTemp, Warning, TEXT("Put your mouse cursor"));
    
    //親ウィジェットにデータを渡す
    if (SkillTree)
    {
        UE_LOG(LogTemp, Warning, TEXT("Get Own To SkillTree"));
        if (!ParkData)return;

        SkillTree->PerkDesc->SetText(ParkData->Description);
        SkillTree->PerkName->SetText(ParkData->DisplayName);
    }
}

void USkillNodeWidget::Init(UParkData* InData, UParkComponent* InComp)
{
    ParkData = InData;
    ParkComp = InComp;

    if (NameText && ParkData)
    {
        NameText->SetText(ParkData->DisplayName);
    }

    UpdateState();
}

void USkillNodeWidget::UpdateState()
{
    if (!ParkComp || !ParkData) return;

    const bool bOwned = ParkComp->IsParkOwned(ParkData);
    const bool bCan = ParkComp->CanAcquirePark(ParkData);

    if (bOwned)
    {
        NodeButton->SetIsEnabled(true);
        SetRenderOpacity(1.0f);
    }
    else if (bCan)
    {
        NodeButton->SetIsEnabled(true);
        SetRenderOpacity(1.0f);
    }
    else
    {
        NodeButton->SetIsEnabled(false);
        SetRenderOpacity(0.1f);
    }
}

void USkillNodeWidget::OnClicked()
{
    if (!ParkComp || !ParkData) return;

    if (ParkComp->CanAcquirePark(ParkData))
    {
        ParkComp->ApplyPark(ParkData);
    }
}