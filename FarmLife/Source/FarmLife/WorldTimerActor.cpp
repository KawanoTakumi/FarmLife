// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTimerActor.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AWorldTimerActor::AWorldTimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldTimerActor::BeginPlay()
{
	Super::BeginPlay();
    //レベル開始でタイマー作動
    GetWorld()->GetTimerManager().SetTimer(WorldTimerHandle,this,&AWorldTimerActor::OnTimerFinished,max_timer,false);
    //一秒毎のタイマー
    GetWorldTimerManager().SetTimer(OnCountSecond, this, &AWorldTimerActor::OnCountToSecound, 1.0f, true);
    //タイマーの最大値を設定
    timer_remain = max_timer;

    //プレイヤー取得
    if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
        Player = Cast<APlayerCharacter>(character);
}

// Called every frame
void AWorldTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldTimerActor::OnTimerFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("Timer Finished"));

    //ゲームオーバーをここで生成


    //タイマー停止
    GetWorld()->GetTimerManager().ClearTimer(WorldTimerHandle);
    GetWorldTimerManager().ClearTimer(OnCountSecond);
}

//一秒毎のタイマー
void AWorldTimerActor::OnCountToSecound()
{
    if (timer_remain > 0)
        timer_remain -= 1.0f;//一秒減らす

    //widget更新
    if (Player)
    {
        Player->UpdateWorldTimer(timer_remain);
    }
}