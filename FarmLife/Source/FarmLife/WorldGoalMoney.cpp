// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGoalMoney.h"
#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
// Sets default values
AWorldGoalMoney::AWorldGoalMoney()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldGoalMoney::BeginPlay()
{
	Super::BeginPlay();
	
	//プレイヤー取得
	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
		Player = Cast<APlayerCharacter>(character);

	if (Player)
	{
		Player->GoalMoney = goal_money;
		UE_LOG(LogTemp, Warning, TEXT("set_money %d"),Player->GoalMoney);
	}
		
}

// Called every frame
void AWorldGoalMoney::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//目標金額を渡す
int32 AWorldGoalMoney::ReturnGoalMoney()
{
	return goal_money;
}