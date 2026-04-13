// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClop.h"

// Sets default values
ABaseClop::ABaseClop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseClop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseClop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

