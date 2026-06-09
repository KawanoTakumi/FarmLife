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
			mesh->SetStaticMesh(crop_data->mesh);

		//爆発するか設定
		if (crop_data->crop_type == CropType::Explosive)
			isExplosive = true;
		//凍結するか設定
		if (crop_data->crop_type == CropType::Cold)
			isCold = true;

	}

	//ゲームインスタンス
	G_GameInstance = GetWorld()->GetGameInstance<UGrobalGameInstance>();


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
		
	if(Damage_Effect)
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Damage_Effect, GetActorLocation(), GetActorRotation());
	if (m_current_hp <= 0)
	{
		Harvest(false);
		if(Kill_Effect)
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Kill_Effect,GetActorLocation(),GetActorRotation());
	}
	return DamageAmount;
}

void ABaseCrop::Harvest(bool OnEnemy)
{
	if (!OnEnemy)
	{
		if (G_GameInstance)
		{
			G_GameInstance->g_use_count++;
			UE_LOG(LogTemp, Warning, TEXT("add_count : %d"), G_GameInstance->g_use_count);
		}
			
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
	if (isExplosive)
		Explosive();
	if (isCold)
		Cold();

	Destroy();
}

void ABaseCrop::Explosive()
{
	FVector m_this_location = GetActorLocation();//爆発の中心座標
	m_this_location.Z -= 100.0f;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(m_explosive_area);

	bool bHasHit = GetWorld()->SweepMultiByChannel(
		m_hit_character, m_this_location, m_this_location, FQuat::Identity,
		ECC_Pawn, Sphere);

	if (bHasHit)
	{
		for (FHitResult& hit : m_hit_character)
		{
			if (hit.GetActor()->ActorHasTag("Player"))
			{
				UE_LOG(LogTemp, Warning, TEXT("ExplosivePlayer"));
				
				APlayerCharacter* player = Cast<APlayerCharacter>(hit.GetActor());
				//距離と方向の計算
				FVector dir = m_this_location - player->GetActorLocation();
				dir.Normalize();
				FVector FinalLaunchVelocity = -dir * m_explosive_power;
				player->LaunchCharacter(FinalLaunchVelocity,true,true);
			}
		}
	}
}

void ABaseCrop::Cold()
{
	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		APlayerCharacter* player_character = Cast<APlayerCharacter>(character);
		
		if (player_character)
		{
			UE_LOG(LogTemp, Warning, TEXT("ColdPlayer"));
			player_character->ColdToPlayer();
		}
	}
}