// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCrop.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"

// Sets default values
ABaseCrop::ABaseCrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void ABaseCrop::BeginPlay()
{
	Super::BeginPlay();
	if (crop_data)
	{
		//体力設定
		m_current_hp = crop_data->max_hp;

		//メッシュ設定
		if (crop_data->mesh)
		{
			mesh->SetStaticMesh(crop_data->mesh);
		}
		//爆発するか設定
		if (crop_data->crop_type == CropType::Explosive)
			isExplasive = true;
	}
}

// Called every frame
void ABaseCrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCrop::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	m_current_hp -= DamageAmount;
	if (m_current_hp <= 0)
	{
		Harvest(false);
	}
	return DamageAmount;
}

void ABaseCrop::Harvest(bool OnEnemy)
{
	if (!OnEnemy)
	{
		if (crop_data)
		{
			//ここでお金を取得し、プレイヤーに渡す
			if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
			{
				APlayerCharacter* player_character = Cast<APlayerCharacter>(character);

				if (player_character)
				{
					player_character->AddMoney(crop_data->drop_money);
				}
			}
		}
	}
	//爆発する作物の場合
	if (isExplasive)
		Explosive();
	Destroy();
}

void ABaseCrop::Explosive()
{
	FVector m_this_location = GetActorLocation();//爆発の中心座標

	float explosive_area = 100.0f;//爆発範囲

	TArray<FHitResult> hit_character;//当たったキャラクター

	FCollisionShape Sphere = FCollisionShape::MakeSphere(explosive_area);

	bool bHasHit = GetWorld()->SweepMultiByChannel(
		hit_character, m_this_location, m_this_location, FQuat::Identity,
		ECC_Pawn, Sphere);

	if (bHasHit)
	{
		for (auto& Hit : hit_character)
		{
			// ヒットしたコンポーネントを取得
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());
			if (RootComp)
			{
				RootComp->AddRadialImpulse(
					m_this_location,
					explosive_area,
					250.0f,
					ERadialImpulseFalloff::RIF_Linear,
					true
				);
			}
		}
	}
}