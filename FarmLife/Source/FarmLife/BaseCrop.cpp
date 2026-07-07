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

		//作物の種類に応じてエフェクトを発生させるか決める
		switch (crop_data->crop_type)
		{
		default:
			break;
		case CropType::Normal:
		case CropType::Corrupted:
			break;
		case CropType::Explosive:isExplosive = true;
			break;
		case CropType::Cold:isCold = true;
			break;
		case CropType::Dust:isDust = true;
			break;
		case CropType::Spark:isSpark = true;
			break;

		}
	}

	set_se = GetComponentByClass<USetSEComponent>();
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
	if (set_se && Damage_SE)
		set_se->PlaySound(Damage_SE);
	if (m_current_hp <= 0)
	{
		Harvest(false);
		if(Kill_Effect)
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Kill_Effect,GetActorLocation(),GetActorRotation());
		if (set_se && Kill_SE)
			set_se->PlaySound(Kill_SE);
	}
	return DamageAmount;
}

void ABaseCrop::Harvest(bool OnEnemy)
{
	if (!OnEnemy)
	{
		if (G_GameInstance)
			G_GameInstance->g_use_count++;
		if (crop_data)
		{
			//ここでお金を取得し、プレイヤーに渡す
			if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
			{
				APlayerCharacter* player_character = Cast<APlayerCharacter>(character);

				if (player_character)
					player_character->AddMoney(crop_data->drop_money,false);
			}
		}
	}
	//エフェクトを発生させるか
	if (isExplosive)
		Explosive();
	if (isCold)
		Effects(0);
	if (isDust)
		Effects(1);
	if (isSpark)
		Effects(2);

	Destroy();
}

void ABaseCrop::Explosive()
{


	//爆発の中心座標
	FVector m_this_location = GetActorLocation();
	//少し座標を下にして打ち上げれるように設定
	m_this_location.Z -= 100.0f;
	//球体コリジョンを作成
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
				APlayerCharacter* player = Cast<APlayerCharacter>(hit.GetActor());
				
				//爆発耐性を持っていた場合、ここで終了する
				if (player->isExplosiveResist)
					return;

				//距離と方向の計算
				FVector dir = m_this_location - player->GetActorLocation();
				dir.Normalize();
				//最終的な発射方向を設定
				FVector FinalLaunchVelocity = -dir * m_explosive_power;
				player->LaunchCharacter(FinalLaunchVelocity,true,true);
			}
		}
	}
}

void ABaseCrop::Effects(int _effect_number)
{
	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		APlayerCharacter* player_character = Cast<APlayerCharacter>(character);

		if (player_character)
		{
			switch (_effect_number)
			{
			default:
				break;
			case 0:	player_character->ColdToPlayer();
				break;
			case 1:	player_character->DustToPlayer();
				break;
			case 2: player_character->SparkToPlayer();
				break;
			}
		}
	}
}