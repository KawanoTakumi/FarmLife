// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrobalGameInstance.h"
#include "TrophyViewActor.generated.h"

UCLASS()
class FARMLIFE_API ATrophyViewActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrophyViewActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Sランクを取った時に表示するトロフィー群
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trophy")
	TArray<AActor*> trophy_Objects;

	//トロフィーを表示する
	UFUNCTION()
	void ViewTrophies();

private:
	UGrobalGameInstance* game_instance;//グローバルインスタンス
};
