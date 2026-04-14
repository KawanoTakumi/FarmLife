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

	UPROPERTY(EditAnywhere, Category = "Crops")
	TArray<TSubclassOf<ABaseCrop>> CropClass;
};