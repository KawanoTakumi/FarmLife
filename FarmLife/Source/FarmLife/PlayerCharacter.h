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
#include "ParkComponent.h"
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

	void AddMoney(int32 amount);//お金追加
	void UpdateTimer(int32 timer);//タイマー更新
	//インプットマッピングコンテキスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
	UInputMappingContext* InputMapingContext;

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
	UInputAction* IntractAction;

	//カメラ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "camera")
	UCameraComponent* FirstPersonCamera;

	//ゲームのメインUIウィジェットクラス
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGameMainUserWidget> GameMainUserWidgetClass;

	//ゲームのメインUI
	UPROPERTY()
	UGameMainUserWidget* GameMainUserWidget;

	//パーク用インタラクトオブジェクト
	UPROPERTY()
	AGetParkObj* GetPerkObject;
	
	//パークコンポーネント
	UPROPERTY()
	UParkComponent* ParkComponent;
private:
	int32 money = 0;//所持金
	int32 atk_power = 1;//攻撃力
	int32 atk_radius = 90;//攻撃範囲
	
};