// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Bee.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemy_Bee::AEnemy_Bee()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Bee::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);//飛行モードを使用
}

// Called every frame
void AEnemy_Bee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//付近の作物を探し目標に設定する
	if (!TargetCrop)
		FindNearCrop();
	else
	{
		float Distance = FVector::Dist(GetActorLocation(), TargetCrop->GetActorLocation());

		if (Distance <= Attack_Range)
			Attack();
	}
}

void AEnemy_Bee::FindNearCrop()
{
	TArray<AActor*> FoundCrops;

	//BaseCropをすべて探す
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCrop::StaticClass(), FoundCrops);
	if (FoundCrops.Num() < 1)return;

	float NearestDistance = MAX_FLT;

	for (AActor* Actor : FoundCrops)
	{
		float dist = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
		if (dist < NearestDistance)
		{
			NearestDistance = dist;
			TargetCrop = Cast<ABaseCrop>(Actor);
		}
	}
}

void AEnemy_Bee::MoveToCrop(float Delta)
{
	if (!TargetCrop)return;
	FVector Direction = (TargetCrop->GetActorLocation() - GetActorLocation());//移動ベクトル作成
	AddActorWorldOffset(Direction * Move_Speed * Delta);
	SetActorRotation(Direction.Rotation());
}
void AEnemy_Bee::Attack()
{
	//攻撃されたらその作物は即座に削除される
	TargetCrop->Harvest(true);
}