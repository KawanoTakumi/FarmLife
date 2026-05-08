// Fill out your copyright notice in the Description page of Project Settings.


#include "GetParkObj.h"
#include "PlayerCharacter.h"
#include "WorldTimerActor.h"
#include "Kismet/GameplayStatics.h"
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
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGetParkObj::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AGetParkObj::OnOverlapEnd);
}

// Called every frame
void AGetParkObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGetParkObj::OpenUIWidget(AActor* OtherActor)
{
	//パーク取得用のUIを表示できるようにする
	if (OtherActor)
	{
		APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
		
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PC && PlayerController)
		{
			//ここでWidgetを作成する
			if (SkillTreeWidgetClass)
				SkillTreeWidget = CreateWidget<USkillTreeWidget>(GetWorld(), SkillTreeWidgetClass);


			if (SkillTreeWidget && !IsUI)
			{
				IsUI = true;
				SkillTreeWidget->AddToViewport();
				
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				PlayerController->SetInputMode(InputMode);
				SkillTreeWidget->OnClosed.AddDynamic(this, &AGetParkObj::OnWidgetClosed);
				SkillTreeWidget->CreateWidgetData();
				PlayerController->SetIgnoreMoveInput(true);
			}

		}
	}

}

//接触時の挙動
void AGetParkObj::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	IsPlayerInside = true;
	AActor* FoundTimer = 
	UGameplayStatics::GetActorOfClass(GetWorld(),AWorldTimerActor::StaticClass());
	AWorldTimerActor* worldTimer = Cast<AWorldTimerActor>(FoundTimer);

	if(worldTimer)
	worldTimer->PawsTimer();

	APlayerCharacter* PC = Cast<APlayerCharacter>(OtherActor);
	PC->GetPerkObject = this;
}

void AGetParkObj::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	AActor* FoundTimer =
		UGameplayStatics::GetActorOfClass(GetWorld(), AWorldTimerActor::StaticClass());
	AWorldTimerActor* worldTimer = Cast<AWorldTimerActor>(FoundTimer);

	if (worldTimer)
		worldTimer->UnPawsTimer();

	IsPlayerInside = false;
	IsUI = false;
}