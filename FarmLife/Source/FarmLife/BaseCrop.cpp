// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCrop.h"
#include "Kismet/GameplayStatics.h"
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
		Harvest();
	}
	return DamageAmount;
}

void ABaseCrop::Harvest()
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
	Destroy();
}