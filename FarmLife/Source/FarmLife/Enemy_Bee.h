// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCrop.h"
#include "Enemy_Bee.generated.h"

UCLASS()
class FARMLIFE_API AEnemy_Bee : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Bee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	ABaseCrop* TargetCrop;//”j‰ó‚·‚éì•¨

	void FindNearCrop();//•t‹ß‚Ìì•¨‚ğ’T‚·
	void MoveToCrop(float Delta);//–Ú“I‚Ìì•¨‚Ü‚ÅˆÚ“®‚·‚é
	void Attack();//UŒ‚ŠÖ”
public:
	//ì•¨‚É—^‚¦‚éƒ_ƒ[ƒW
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "combat")
	float Attack_Damage = 1.0f;

	//ì•¨‚Ö‚ÌUŒ‚”ÍˆÍ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "combat")
	float Attack_Range = 50.0f;

	//ˆÚ“®‘¬“x
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "combat")
	float Move_Speed = 50.0f;
};