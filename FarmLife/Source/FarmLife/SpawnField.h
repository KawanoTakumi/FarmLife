// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCrop.h"
#include "SpawnField.generated.h"

UCLASS()
class FARMLIFE_API ASpawnField : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetRandomPointInField()const;

	void SpawnCrops(int32 count);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FieldMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crops")
	TArray<TSubclassOf<ABaseCrop>> CropClass;

	UPROPERTY()
	TArray<ABaseCrop*> SpawnedCrops;

	UPROPERTY(EditAnywhere, Category = "UI")
	class UGameMainUserWidget* GameMainWidgetRef;

	//接触時
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	//非接触時
	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void OnDerayEnd();

	void OnCountToSecound();//時間計測

	void AddCrop(TSubclassOf<ABaseCrop> crop_class);

private:
	FTimerHandle EndOverlapTimer;//非接触時のタイマー
	FTimerHandle OnFieldTimer;//畑内にいる場合のタイマー
	FTimerHandle OnCountSecond;//一秒を計測する用のタイマー
	bool IsInvidePlayer = false;//プレイヤーが畑内にいるかどうか
	float RemainingTimer = 0.0f;//残り時間
	float MaxTimer = 5.0f;//最大出現時間
	float DerayTimer = 0.3f;//場外にいた場合の消失時間
	int   MaxSpwanCount = 10;//最大出現数
	class APlayerCharacter* player;
};