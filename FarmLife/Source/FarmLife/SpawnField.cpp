// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnField.h"
#include "BaseCrop.h"
// Sets default values
ASpawnField::ASpawnField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldMesh"));
	RootComponent = FieldMesh;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(FieldMesh);
}

// Called when the game starts or when spawned
void ASpawnField::BeginPlay()
{
	Super::BeginPlay();
	SpawnCrops(25);
}

// Called every frame
void ASpawnField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnField::GetRandomPointInField() const
{
	FVector origin = SpawnArea->GetComponentLocation();
	FVector extent = SpawnArea->GetScaledBoxExtent();

	float X = FMath::RandRange(-extent.X, extent.X);
	float Y = FMath::RandRange(-extent.Y, extent.Y);

	return origin + FVector(X, Y, 0.0f);
}

void ASpawnField::SpawnCrops(int32 count)
{
	for (int i = 0; i < count; i++)
	{
		FVector Location = GetRandomPointInField();

		int32 index = FMath::RandRange(0, CropClass.Num() - 1);
		TSubclassOf<ABaseCrop> select = CropClass[index];

		GetWorld()->SpawnActor<ABaseCrop>(
		select,
		Location,
		FRotator::ZeroRotator
		);
	}
}