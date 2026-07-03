// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameMainUserWidget.h"
#include "SpawnField.h"
#include "GetParkObj.h"
#include "PauseWidget.h"
#include "ParkComponent.h"
#include "WorldGoalMoney.h"
#include "GrobalGameInstance.h"
#include "NiagaraSettingComponent.h"
#include "SetSEComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FARMLIFE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);//移動関数

	void Look(const FInputActionValue& Value);//視点移動関数

	void Attack();//攻撃関数

	void Interact();//接触関数

	void Pause();//一時停止

	void AddMoney(int32 amount);//お金追加

	int32 ReturnMoney();//お金の値を返す

	void UpdateTimer(int32 timer);//タイマー更新

	void UpdateWorldTimer(int32 world_timer);//ワールドタイム更新

	void CountHoeUse();//鍬の使用回数計算

	void GoToResult(bool clear);//リザルト画面移行

	void EffectToPlayer(UNiagaraSystem* _effect,USoundBase* _sound,FVector color,float _move_speed);

	void ColdToPlayer();//凍結

	void FinishedEffectToPlayer();//凍結終了

	void DustToPlayer();//視界不良

	void SparkToPlayer();//感電

	void OnWidgetClosed() { PauseWidget = nullptr; };//UIを削除する

	void UnPauseImageChange();


	//インプットマッピングコンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputMappingContext* InputMappingContext;

	//移動IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputAction* MoveAction;

	//視点移動IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputAction* LookAction;

	//攻撃IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputAction* AttackAction;

	//インタラクトIA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputAction* InteractAction;

	//一時停止IA
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputAction* PauseAction;

	//カメラ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "camera")
	UCameraComponent* FirstPersonCamera;

	//ゲームのメインUIウィジェットクラス
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGameMainUserWidget> GameMainUserWidgetClass;

	//一時停止のUIウィジェットクラス
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseWidget> PauseWidgetClass;

	//エフェクト配列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TArray<UNiagaraSystem*> Effects;

	//エフェクトSE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SE")
	TArray<USoundBase*> Effect_SE;

	//一時停止用画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UTexture2D* PauseImage;

	//一時停止解除画像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UTexture2D* UnPauseImage;

	//ゲームのメインUI
	UPROPERTY()
	UGameMainUserWidget* GameMainUserWidget;

	//一時停止用UI
	UPROPERTY()
	UPauseWidget* PauseWidget;

	//パーク用インタラクトオブジェクト
	UPROPERTY()
	AGetParkObj* GetPerkObject;

	//パークコンポーネント
	UPROPERTY()
	UParkComponent* perk_component;

	//ゲームクリアの必要な金額
	UPROPERTY()
	int32 GoalMoney;

	//グローバルゲームインスタンス
	UPROPERTY()
	UGrobalGameInstance* G_GameInstance;

	UPROPERTY()
	bool isPause = false;


private:
	int32 money = 0;//所持金
	int32 atk_power = 1;//攻撃力
	int32 atk_radius = 90;//攻撃範囲
	int32 use_hoe_count = 30;//採取可能回数
	int32 use_max_count = 30;//最大採取可能回数
	float move_speed = 1.0f;
	FTimerHandle effect_timer;
	UNiagaraSettingComponent* effect_component;//エフェクトコンポーネント
	USetSEComponent* set_sound_comp;
};