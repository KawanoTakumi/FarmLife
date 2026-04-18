// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SkillTreeWidget.h"
#include "Components/BoxComponent.h"
#include "GetParkObj.generated.h"

UCLASS()
class FARMLIFE_API AGetParkObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGetParkObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsUI = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "mesh")
	UStaticMeshComponent* ParkHatMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "mesh")
	UBoxComponent* CollisionBox;

	UPROPERTY()
	bool bPlayerInRAnge = false;

	//パークツリーUI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<USkillTreeWidget> SkillTreeWidgetClass;

	USkillTreeWidget* SkillTreeWidget;

	//接触時
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	//非接触時
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnWidgetClosed()
	{
		SkillTreeWidget = nullptr;
	}
};
