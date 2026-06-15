// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraSettingComponent.h"

// Sets default values for this component's properties
UNiagaraSettingComponent::UNiagaraSettingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNiagaraSettingComponent::BeginPlay()
{
	Super::BeginPlay();
	FindAndCacheNiagara();
	// ...
	
}


// Called every frame
void UNiagaraSettingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNiagaraSettingComponent::FindAndCacheNiagara()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		CacheNiagaraComp = Owner->FindComponentByClass<UNiagaraComponent>();
	}

}

void UNiagaraSettingComponent::SetVFXVisible(bool bVisible)
{
	if (!CacheNiagaraComp)FindAndCacheNiagara();

	if (CacheNiagaraComp)
	{
		if (bVisible)
		{
			CacheNiagaraComp->SetVisibility(true);
			CacheNiagaraComp->Activate();
		}
		else
		{
			CacheNiagaraComp->Deactivate();
			CacheNiagaraComp->SetVisibility(false);
		}
	}
}

void UNiagaraSettingComponent::ChangeVFXAsset(UNiagaraSystem* nEffect)
{
	if (!CacheNiagaraComp) FindAndCacheNiagara();

	if (CacheNiagaraComp && NewEffect)
	{
		CacheNiagaraComp->SetAsset(NewEffect);
		CacheNiagaraComp->Activate(true);
	}
}