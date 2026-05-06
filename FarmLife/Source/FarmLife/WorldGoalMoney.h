// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGoalMoney.generated.h"

UCLASS()
class FARMLIFE_API AWorldGoalMoney : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldGoalMoney();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Money")
	int32 goal_money = 0;

	int32 ReturnGoalMoney();

private:
	class APlayerCharacter* Player;
};