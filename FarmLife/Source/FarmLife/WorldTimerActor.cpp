// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTimerActor.h"

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
    GetWorld()->GetTimerManager().SetTimer(
        worldtimerhandle,
        this,
        &AWorldTimerActor::OnTimerFinished,
        max_timer,
        false
    );
}

// Called every frame
void AWorldTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldTimerActor::OnTimerFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("Timer Finished"));
}