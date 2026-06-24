// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WorldTimerActor.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//ボタンの関数バインド
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClickedBack);

	if(TitleButton)
		TitleButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClickedTitle);
}

void UPauseWidget::OnClickedBack()
{
	//プレイヤーコントローラを取得
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	//タイマーを取得し、タイマーを再稼働させる
	AActor* FoundTimer =
		UGameplayStatics::GetActorOfClass(GetWorld(), AWorldTimerActor::StaticClass());
	AWorldTimerActor* worldTimer = Cast<AWorldTimerActor>(FoundTimer);

	if (worldTimer)
		worldTimer->UnPauseTimer();

	if (!PC) return;
	//接続解除
	RemoveFromParent();
	// 入力をゲームに戻す
	PC->bShowMouseCursor = false;
	FInputModeGameOnly Mode;
	PC->SetInputMode(Mode);
	PC->SetIgnoreMoveInput(false);
}

void UPauseWidget::OnClickedTitle()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(this,FName("Title"));
}