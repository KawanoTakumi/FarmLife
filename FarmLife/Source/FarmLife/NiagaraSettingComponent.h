// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraSettingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMLIFE_API UNiagaraSettingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNiagaraSettingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//VFX描画管理関数
	UFUNCTION(BlueprintCallable, Category = "VFX Control")
	void SetVFXVisible(bool bVisible);

	//VFX入れ替え関数
	UFUNCTION(BlueprintCallable, Category = "VFX Control")
	void ChangeVFXAsset(UNiagaraSystem* nEffect);

	UPROPERTY()
	UNiagaraComponent* CacheNiagaraComp;//同じコンポーネントをキャッシュする用

	void FindAndCacheNiagara();//キャッシュ関数
};