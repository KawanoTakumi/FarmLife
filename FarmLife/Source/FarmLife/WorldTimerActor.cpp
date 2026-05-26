// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTimerActor.h"
#include "Kismet/GameplayStatics.h"
#include "GrobalGameInstance.h"
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
    GetWorldTimerManager().SetTimer(OnCountSecond, this, &AWorldTimerActor::OnCountToSecond, 1.0f, true);
    //タイマーの最大値を設定
    timer_remain = max_timer;

    //プレイヤー取得
    if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
        Player = Cast<APlayerCharacter>(character);

    //最大時間をコピー
    if (UGrobalGameInstance* g_gameinstance = GetWorld()->GetGameInstance<UGrobalGameInstance>())
        g_gameinstance->g_max_timer = max_timer;
}

// Called every frame
void AWorldTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldTimerActor::OnTimerFinished()
{
    //タイマー停止
    GetWorld()->GetTimerManager().ClearTimer(WorldTimerHandle);
    GetWorldTimerManager().ClearTimer(OnCountSecond);

    //ゲームオーバーをここで生成
    if (Player)
        Player->GoToResult(false);

}

//一秒毎のタイマー
void AWorldTimerActor::OnCountToSecond()
{
    if (timer_remain > 0)
        timer_remain -= 1.0f;//一秒減らす

    //widget更新
    if (Player)
    {
        Player->UpdateWorldTimer(timer_remain);
    }
}

void AWorldTimerActor::PawsTimer()
{
    GetWorld()->GetTimerManager().PauseTimer(WorldTimerHandle);
    GetWorldTimerManager().PauseTimer(OnCountSecond);
}

void AWorldTimerActor::UnPawsTimer()
{
    GetWorld()->GetTimerManager().UnPauseTimer(WorldTimerHandle);
    GetWorldTimerManager().UnPauseTimer(OnCountSecond);
}