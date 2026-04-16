// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnField.h"
#include "BaseCrop.h"
#include "PlayerCharacter.h"
#include "GameMainUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnField::ASpawnField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldMesh"));
	RootComponent = FieldMesh;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(FieldMesh);
	SpawnArea->SetGenerateOverlapEvents(true);
	SpawnArea->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ASpawnField::BeginPlay()
{
	Super::BeginPlay();
	SpawnArea->OnComponentBeginOverlap.AddDynamic(this, &ASpawnField::OnOverlapBegin);
	SpawnArea->OnComponentEndOverlap.AddDynamic(this, &ASpawnField::OnOverlapEnd);

	//ÉvÉåÉCÉÑÅ[éÊìæ
	if (ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		player = Cast<APlayerCharacter>(character);
	}
}

// Called every frame
void ASpawnField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnField::GetRandomPointInField() const
{
	FVector origin = SpawnArea->GetComponentLocation();
	FVector extent = SpawnArea->GetScaledBoxExtent();

	float X = FMath::RandRange(-extent.X, extent.X);
	float Y = FMath::RandRange(-extent.Y, extent.Y);

	return origin + FVector(X, Y, 0.0f);
}

void ASpawnField::SpawnCrops(int32 count)
{
	for (int i = 0; i < count; i++)
	{
		FVector Location = GetRandomPointInField();

		int32 index = FMath::RandRange(0, CropClass.Num() - 1);
		TSubclassOf<ABaseCrop> select = CropClass[index];

		ABaseCrop* thisCrop = GetWorld()->SpawnActor<ABaseCrop>(
		select,
		Location,
		FRotator::ZeroRotator
		);

		//îzóÒÇ…äiî[ÇµÇƒÇ®Ç≠
		if (thisCrop)
			SpawnedCrops.Add(thisCrop);
	}
}

//ê⁄êGéû
void ASpawnField::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if (!OtherActor)return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		GetWorldTimerManager().ClearTimer(EndOverlapTimer);
		GetWorldTimerManager().SetTimer(OnFieldTimer,this,&ASpawnField::OnDerayEnd,MaxTimer,false);

		RemainingTimer = MaxTimer;
		player->UpdateTimer(RemainingTimer);
		GetWorldTimerManager().SetTimer(OnCountSecond, this, &ASpawnField::OnCountToSecound, 1.0f, true);

		if (!IsInvidePlayer)
		{
			IsInvidePlayer = true;
			SpawnCrops(MaxSpwanCount);
		}
	}
}

//îÒê⁄êGéû
void ASpawnField::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(EndOverlapTimer, this, &ASpawnField::OnDerayEnd, DerayTimer, false);
	}
}

//îÒê⁄êGéûíxâÑèàóù
void ASpawnField::OnDerayEnd()
{
	if (IsInvidePlayer)
	{
		for (ABaseCrop* Crop : SpawnedCrops)
		{
			//íÜêgÇ™Ç†ÇÈèÍçáÇÃÇ›çÌèú
			if (IsValid(Crop))
			{
				Crop->Destroy();
			}
		}
		//èâä˙âª
		SpawnedCrops.Empty();
		RemainingTimer = 0;
		player->UpdateTimer(RemainingTimer);
		IsInvidePlayer = false;
	}
}

//éûä‘åvë™
void ASpawnField::OnCountToSecound()
{
	if(RemainingTimer > 0)
	RemainingTimer -= 1.0f;//àÍïbå∏ÇÁÇ∑

	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("count to timer"));
		player->UpdateTimer(RemainingTimer);
	}

	if (RemainingTimer <= 1)
	{
		RemainingTimer = 0;
		GetWorldTimerManager().ClearTimer(OnCountSecond);
	}
}

//êVãKçÏï®í«â¡
void ASpawnField::AddCrop(TSubclassOf<ABaseCrop> crop_class)
{
	CropClass.Add(crop_class);
}