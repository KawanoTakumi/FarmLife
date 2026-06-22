// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SetSEComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//カメラ設定
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FirstPersonCamera-> SetupAttachment(RootComponent);
	FirstPersonCamera-> SetRelativeLocation(FVector(0,0,50));
	FirstPersonCamera-> bUsePawnControlRotation = true;
	
	bUseControllerRotationYaw    = true;
	bUseControllerRotationPitch  = true;
	bUseControllerRotationRoll   = false;

	//移動設定
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//コントローラー取得
	if (APlayerController* player_controller = Cast<APlayerController>(GetController()))
	{
		player_controller->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		player_controller->SetInputMode(InputMode);

		if (ULocalPlayer*  local_player = player_controller->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* subsystem =
				local_player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				subsystem->AddMappingContext(InputMappingContext,0);
			}
		}
	}
	//各コンポーネントを探す
	perk_component = FindComponentByClass<UParkComponent>();
	effect_component = FindComponentByClass<UNiagaraSettingComponent>();
	if (effect_component)
	{
		effect_component->SetVFXVisible(false);
		effect_component->ChangeVFXAsset(effect_component->NewEffects[0]);
	}
			//UI生成
	if (GameMainUserWidgetClass)
	{
		GameMainUserWidget = CreateWidget<UGameMainUserWidget>(GetWorld(), GameMainUserWidgetClass);
		if (GameMainUserWidget)
		{
			GameMainUserWidget->AddToViewport();
		}
	}

	//ウィジェット更新
	if (GameMainUserWidget)
	{
		GameMainUserWidget->UpdateHoeCount(use_hoe_count, use_max_count + perk_component->max_hoe_count);
		GameMainUserWidget->SetQuestMoney(GoalMoney);
	}
		
	//ゲームインスタンス取得
	G_GameInstance = GetWorld()->GetGameInstance<UGrobalGameInstance>();
	G_GameInstance->g_use_count = 0;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//各入力を設定
	if (UEnhancedInputComponent* enhanced_input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhanced_input->BindAction(MoveAction,    ETriggerEvent::Triggered, this, &APlayerCharacter::Move);//移動
		enhanced_input->BindAction(LookAction,    ETriggerEvent::Triggered, this, &APlayerCharacter::Look);//視点移動
		enhanced_input->BindAction(AttackAction,  ETriggerEvent::Started,   this, &APlayerCharacter::Attack);//攻撃
		enhanced_input->BindAction(InteractAction, ETriggerEvent::Started,   this, &APlayerCharacter::Interact);//インタラクト
	}
}

//移動関数
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	//移動ベクトルを取得し、移動速度を掛ける
	FVector2D input_vector = Value.Get<FVector2D>();
	input_vector *= move_speed;

	//コントローラを取得できた時だけ移動させる
	if (Controller != nullptr)
	{
		const FRotator rotation  = Controller->GetControlRotation();
		const FRotator yaw_rotation(0,rotation.Yaw,0);
		const FVector  forward   = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		const FVector  right     = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward, input_vector.Y);
		AddMovementInput(right,   input_vector.X);
	}
}

//視点移動関数
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D lookVector = Value.Get<FVector2D>();

	AddControllerYawInput  (lookVector.Y);
	AddControllerPitchInput(lookVector.X);
}

//攻撃関数
void APlayerCharacter::Attack()
{
	//カメラの位置から向いている方向に200f掛けた値まで攻撃の判定を出す
	FVector start = FirstPersonCamera->GetComponentLocation();
	//開始位置を少しずらす
	FVector forward = FirstPersonCamera->GetForwardVector();
	FVector end     = start + (forward * 200.0f);

	float radius    = atk_radius;//攻撃の範囲
	int   m_calc_attack = atk_power + perk_component->attack_bonus;
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool flag_hit = GetWorld()->SweepSingleByChannel(
		hit, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_Visibility, 
		FCollisionShape::MakeSphere(radius)
	);

	//接触
	if (flag_hit)
	{
		if (hit.GetActor()->ActorHasTag("Crop"))
		{
			CountHoeUse();
			UGameplayStatics::ApplyDamage(
				hit.GetActor(),
				m_calc_attack,
				GetController(),
				this,
				nullptr);
		}
	}
}

//接触関数
void APlayerCharacter::Interact()
{

	if (GetPerkObject && GetPerkObject->IsPlayerInside)
		GetPerkObject->OpenUIWidget(this);
}

void APlayerCharacter::AddMoney(int32 amount)
{
	money += amount * perk_component->multi_bonus;
	if (money < 0)money = 0;

	//お金が目標金額になったらクリアさせる
	if (money >= GoalMoney)
		GoToResult(true);

	//UI更新
	if (GameMainUserWidget)
		GameMainUserWidget->UpdateMoney(money);
}

int32 APlayerCharacter::ReturnMoney()
{
	return money;
}

void APlayerCharacter::UpdateTimer(int32 timer)
{
	if (GameMainUserWidget)
		GameMainUserWidget->UpdateTimer(timer);
}

void APlayerCharacter::UpdateWorldTimer(int32 world_timer)
{
	if (GameMainUserWidget)
	{
		GameMainUserWidget->UpdateWorldTimer(world_timer);
		G_GameInstance->g_timer = world_timer;
	}
}

void APlayerCharacter::CountHoeUse()
{
	//使用回数が0以下の場合お金を減らす
	if (use_hoe_count < 2)
	{
		if (money > 4)
		{
			use_hoe_count = use_max_count + perk_component->max_hoe_count;
			money -= 4;
		}
		else
		{
			GoToResult(false);
		}
	}
	else
	{
		use_hoe_count--;
	}

	//表示更新
	if (GameMainUserWidget)
		GameMainUserWidget->UpdateHoeCount(use_hoe_count, use_max_count + perk_component->max_hoe_count);

}

//リザルト移行
void APlayerCharacter::GoToResult(bool Clear)
{
	if (Clear)
	{
		//ゲームクリア
		G_GameInstance->isWin = true;
		UGameplayStatics::OpenLevel(this, FName("Result_Clear"));
	}
	else
	{
		//ゲームオーバー
		G_GameInstance->isWin = false;
		UGameplayStatics::OpenLevel(this, FName("Result_GameOver"));
	}
}

void APlayerCharacter::ColdToPlayer()
{
	move_speed = 0.3f;
	GetWorld()->GetTimerManager().SetTimer(cold_timer,this,&APlayerCharacter::FinishedColdToPlayer,5.0f);
	//エフェクトを描画
	if (effect_component)
		effect_component->SetVFXVisible(true);

	if (Cold_Sound)
	{
		set_sound_comp->PlaySound(Cold_Sound);
	}

	if (GameMainUserWidget)
	{
		FVector color;
		color.X = 0.3f;
		color.Y = 0.8f;
		color.Z = 0.9f;
		GameMainUserWidget->ChangeFilterEffect(color, 0.3f);
	}
		
}

void APlayerCharacter::FinishedColdToPlayer()
{
	move_speed = 1.0f;
	//エフェクトを解除
	if (effect_component)
		effect_component->SetVFXVisible(false);

	if (GameMainUserWidget)
		GameMainUserWidget->ChangeFilterEffect(FVector::Zero(), 0.0f);
}

void APlayerCharacter::DustToPlayer()
{
	move_speed = 0.6f;
	GetWorld()->GetTimerManager().SetTimer(dust_timer, this, &APlayerCharacter::FinishedDustToPlayer, 8.0f);
	if (effect_component)
		effect_component->SetVFXVisible(true);

	if (Blind_Sound)
	{
		set_sound_comp->PlaySound(Blind_Sound);
	}

	if (GameMainUserWidget)
	{
		FVector color;
		color.X = 0.7f;
		color.Y = 0.5f;
		color.Z = 0.2f;
		GameMainUserWidget->ChangeFilterEffect(color, 0.5f);
	}

}

void APlayerCharacter::FinishedDustToPlayer()
{
	move_speed = 1.0f;
	//エフェクトを解除
	if (effect_component)
		effect_component->SetVFXVisible(false);

	if (GameMainUserWidget)
		GameMainUserWidget->ChangeFilterEffect(FVector::Zero(), 0.0f);

}