// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//ÉJÉÅÉâ
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FirstPersonCamera-> SetupAttachment(RootComponent);
	FirstPersonCamera-> SetRelativeLocation(FVector(0,0,64));
	FirstPersonCamera-> bUsePawnControlRotation = true;
	
	bUseControllerRotationYaw    = true;
	bUseControllerRotationPitch  = true;
	bUseControllerRotationRoll   = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* player_controller = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer*  local_player = player_controller->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* subsystem =
				local_player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				subsystem->AddMappingContext(InputMapingContext,0);
			}
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhanced_input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhanced_input->BindAction(MoveAction,   ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhanced_input->BindAction(LookAction,   ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		enhanced_input->BindAction(AttackAction, ETriggerEvent::Started,   this, &APlayerCharacter::Attack);
	}
}

//à⁄ìÆä÷êî
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D input_vector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator rotation  = Controller->GetControlRotation();
		const FRotator yaw_rotation(0,rotation.Yaw,0);
		const FVector  forward   = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		const FVector  right     = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward, input_vector.Y);
		AddMovementInput(right,   input_vector.X);
	}
}

//éãì_à⁄ìÆä÷êî
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D lookVector = Value.Get<FVector2D>();

	AddControllerYawInput  (lookVector.Y);
	AddControllerPitchInput(lookVector.X);
}

//çUåÇä÷êî
void APlayerCharacter::Attack()
{
	FVector start   = FirstPersonCamera->GetComponentLocation();
	FVector forward = FirstPersonCamera->GetForwardVector();
	FVector end     = start + (forward * 200.0f);

	float radius    = 50.0f;//çUåÇÇÃîÕàÕ

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool flag_hit = GetWorld()->SweepSingleByChannel(
		hit, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_Visibility, 
		FCollisionShape::MakeSphere(radius)
	);

	if (flag_hit)
	{
		UGameplayStatics::ApplyDamage(
		hit.GetActor(),
		1.0f,
		GetController(),
		this,
		nullptr);
	}
}

void APlayerCharacter::AddMoney(int32 amount)
{
	money += amount;
}