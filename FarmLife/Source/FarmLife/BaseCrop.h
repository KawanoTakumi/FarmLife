// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CropData.h"
#include "Components/MeshComponent.h"
#include "BaseCrop.generated.h"

UCLASS()
class FARMLIFE_API ABaseCrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount,FDamageEvent const& DamageEvent,
		AController* EventInstigator,AActor* DamageCauser) override;
	//収穫
	void Harvest(bool OnEnemy);
	//爆発
	void Explosive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UCropData* crop_data;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;

private:
	int32 m_current_hp = 0;
	bool isExplasive = false;
	float m_explosive_area = 500.0f;//爆発範囲
	float m_explasive_power = 1000.0f;//爆発の大きさ
	TArray<FHitResult> m_hit_character;//当たったキャラクター


};