// Fill out your copyright notice in the Description page of Project Settings.

#include "BardPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABardPlayer::ABardPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 800.f;
	SpringArm->AddRelativeRotation(FRotator(-45.f, 25.f, 0.f));
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;

	//Possession
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Orient To Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
}
 
// Called when the game starts or when spawned
void ABardPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if(PlayerSubsystem)
		{
			PlayerSubsystem->AddMappingContext(IMC, 0);
		}
	}
}

// Called every frame
void ABardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EPI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Input Actions
	if(EPI)
	{
		EPI->BindAction(Move, ETriggerEvent::Triggered, this, &ABardPlayer::Movement);
		EPI->BindAction(CombatAction, ETriggerEvent::Started, this, &ABardPlayer::CombatFunction);
		EPI->BindAction(SwapWeapon, ETriggerEvent::Started, this, &ABardPlayer::Weaponswap);
	}
}

void ABardPlayer::Movement(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();
	AddMovementInput(FVector(1,0,0), MovementValue.Y);
	AddMovementInput(FVector(0,1,0), MovementValue.X);
}

void ABardPlayer::CombatFunction()
{
	if (WeaponNumber == 1)
	{
		if (FluteSlash)
		{
			UNiagaraComponent* Slash = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FluteSlash, GetActorLocation(),GetCharacterMovement()->GetLastUpdateRotation()-FRotator(0,90,0));
			//Slash->
			if(!SpawnedFlute)
			SpawnedFlute=GetWorld()->SpawnActor<AActor>(Flute, Position, FRotator(90,0,0));
			SpawnedFlute->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("FluteSocket"));
		}
	
		PlayAnimMontage(FluteAttack);
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Emerald, "Flute");
	}
	if (WeaponNumber == 2)
	{

		//PlayAnimMontage(DrumAttack);
		if (SpawnedFlute)
		{
			SpawnedFlute->Destroy();
			SpawnedFlute = nullptr;
		}
			
		LineTraceStart = GetActorLocation() + GetActorForwardVector() * FVector(100, 0, 0);
		LineTraceEnd = LineTraceStart + FVector(0, 0, -300);

		bool HitSomething=GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility);
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red,false, 2.f);
		
		if(HitSomething)
		{
			AActor* SpawnedDrum = GetWorld()->SpawnActor<AActor>(Drum, FVector(Hit.Location), GetCharacterMovement()->GetLastUpdateRotation());
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Drum");
		}

		if (DrumAOE)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DrumAOE, Hit.Location);
	}
	if (WeaponNumber==3)
	{
		//PlayAnimMontage(HarpAttack);
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, "Harp");
	}
}

void ABardPlayer::Weaponswap()
{
	WeaponNumber++;
	if (WeaponNumber > 3)
		WeaponNumber = 1;
}
