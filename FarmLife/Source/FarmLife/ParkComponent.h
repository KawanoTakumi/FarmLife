// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkData.h"
#include "SpawnField.h"
#include "ParkComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMLIFE_API UParkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//パークの配列
	TArray<UParkData*> OwnedParks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "data")
	ASpawnField* spawnfield;

	float attack_bonus = 0.0f;//攻撃力ボーナス
	float multi_bonus = 1.0f;//価格ボーナス
	float timer_bonus = 0.0f;//時間ボーナス
	int   max_size_bonus = 0;//最大出現数ボーナス

	void ApplyPark(UParkData* park);

	void Recalcurate();
};
