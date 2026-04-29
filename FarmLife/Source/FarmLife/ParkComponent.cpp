// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UParkComponent::UParkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParkComponent::BeginPlay()
{
	Super::BeginPlay();

	spawnfield = Cast<ASpawnField>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnField::StaticClass()));

	// ...
}


// Called every frame
void UParkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//パーク適用
void UParkComponent::ApplyPark(UParkData* data)
{
	if (!data)return;
	if (!CanAcquirePark(data)) return;
	if (data->ParkType == ParkType::AddCrop)
	{
		if (spawnfield)
		{
			spawnfield->AddCrop(data->CropClass);
			spawnfield->AddCrop(data->CorruptedCropClass);
		}
	}
	//取得したパークを取得済み配列に入れる
	OwnedParks.Add(data);


	Recalcurate();//再計算を行う

	OnParkUpdated.Broadcast();
}

//再計算(攻撃力などの場合)
void UParkComponent::Recalcurate()
{
	//いったん値を初期化
	attack_bonus = 0.0f;
	multi_bonus = 1.0f;
	timer_bonus = 0.0f;
	max_size_bonus = 0.0f;
	max_hoe_count = 0;

	for (auto parks : OwnedParks)
	{
		switch (parks->ParkType)
		{
		case ParkType::AddTimer:
		{
			timer_bonus += parks->Value;
			break;
		}
		case ParkType::AddMaxSize:
		{
			max_size_bonus += parks->Value;
			break;
		}
		case ParkType::ValueMag:
		{
			multi_bonus *= parks->Value;
			break;
		}
		case ParkType::AddAttck:
		{
			attack_bonus += parks->Value;
			break;
		}
		case ParkType::AddHoeCount:
		{
			max_hoe_count += parks->Value;
			break;
		}
		}
	}
}

bool UParkComponent::IsParkOwned(UParkData* Data) const
{
	return OwnedParks.Contains(Data);
}

bool UParkComponent::CanAcquirePark(UParkData* Data) const
{
	if (!Data) return false;

	// すでに取得済みなら不可
	if (IsParkOwned(Data)) return false;

	// 前提パークチェック
	for (auto Req : Data->RequiredPerk)
	{
		if (!IsParkOwned(Req))
		{
			return false;
		}
	}

	return true;
}