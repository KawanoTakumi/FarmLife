// Fill out your copyright notice in the Description page of Project Settings.


#include "TrophyViewActor.h"

// Sets default values
ATrophyViewActor::ATrophyViewActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrophyViewActor::BeginPlay()
{
	Super::BeginPlay();


    //ゲームインスタンス取得
    game_instance = GetWorld()->GetGameInstance<UGrobalGameInstance>();

    //隠す
    for (int i = 0; i < trophy_Objects.Num(); i++)
        trophy_Objects[i]->SetActorHiddenInGame(true);

    //トロフィー表示
    ViewTrophies();

}

// Called every frame
void ATrophyViewActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATrophyViewActor::ViewTrophies()
{
    if (game_instance->g_result_rank.Num() > 0)
    {
        for (int i = 0; i < game_instance->g_result_rank.Num(); i++)
        {
            //チェックでオブジェクトがなかった場合は終了
            if (trophy_Objects.Num() < i)return;
            if (game_instance->g_result_rank[i] == 4)
            {
                //表示
                trophy_Objects[i]->SetActorHiddenInGame(false);
            }
        }
    }
}