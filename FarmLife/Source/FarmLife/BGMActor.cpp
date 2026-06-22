// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMActor.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABGMActor::ABGMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABGMActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (Sound)
		UGameplayStatics::PlaySound2D(GetWorld(),Sound);

}

// Called every frame
void ABGMActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

