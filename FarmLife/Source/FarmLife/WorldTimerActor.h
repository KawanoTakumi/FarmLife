// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "WorldTimerActor.generated.h"

UCLASS()
class FARMLIFE_API AWorldTimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldTimerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//タイマーの最大時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "timer")
	float max_timer = 300.0f;
	

	UFUNCTION()
	void OnTimerFinished();//タイマー終了時、ゲームオーバー画面にする

	void OnCountToSecound();

private:
	FTimerHandle WorldTimerHandle;
	FTimerHandle OnCountSecond;//一秒を計測する用のタイマー
	APlayerCharacter* Player;
	float timer_remain = 0.0f;
};