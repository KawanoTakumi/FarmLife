// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodeWidget.h"
#include "SkillTreeWidget.h"
#include "PlayerCharacter.h"
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
    //親ウィジェットにデータを渡す
    if (SkillTree)
    {
        if (!ParkData)return;

        SkillTree->PerkDesc->SetText(ParkData->Description);
        SkillTree->PerkName->SetText(ParkData->DisplayName);
    }
}

void USkillNodeWidget::Init(UParkData* InData, UParkComponent* InComp)
{
    ParkData = InData;
    ParkComp = InComp;
    SetPosition = ParkData->PositionGrid;

    //画像設定
    if (ParkData)
        Icon->SetBrushFromTexture(ParkData->NormalIcon);

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
        Icon->SetBrushFromTexture(ParkData->ClickedIcon);
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
        //画像を変更
        Icon->SetBrushFromTexture(ParkData->ClickedIcon);
        ParkComp->ApplyPark(ParkData);
        //SkillTree->PerkDesc->SetText(FText::FromString(TEXT("このパークは取得できません！")));        
    }
}