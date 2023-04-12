// Fill out your copyright notice in the Description page of Project Settings.


#include "BardPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABardPlayer::ABardPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 800.f;
	SpringArm->AddRelativeRotation(FRotator(-70.f, 25.f, 0.f));
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;

	//Possession
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Orient To Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
		
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
	}
}

void ABardPlayer::Movement(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();
	AddMovementInput(FVector(1,0,0), MovementValue.Y);
	AddMovementInput(FVector(0,1,0), MovementValue.X);
}

