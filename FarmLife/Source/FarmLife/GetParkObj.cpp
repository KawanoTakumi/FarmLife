// Fill out your copyright notice in the Description page of Project Settings.


#include "GetParkObj.h"
#include "PlayerCharacter.h"
// Sets default values
AGetParkObj::AGetParkObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ParkHatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ParkHatMesh"));
	RootComponent = ParkHatMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(ParkHatMesh);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));


}

// Called when the game starts or when spawned
void AGetParkObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGetParkObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//接触時の挙動
void AGetParkObj::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	//パーク取得用のUIを表示する
	if (OtherActor)
	{
		APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
		if (PC)
		{
		}
	}
}

void AGetParkObj::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//パーク取得用のUIを表示する
	if (OtherActor)
	{
		APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
		if (PC)
		{
		}
	}
}
