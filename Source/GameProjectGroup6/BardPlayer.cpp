// Fill out your copyright notice in the Description page of Project Settings.

#include "BardPlayer.h"

#include "DamageHandlingComponent.h"
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
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;

	DrumSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("DrumSpawn"));
	DrumSpawn->SetupAttachment(GetRootComponent());

	DamageHandlingComponent = CreateDefaultSubobject<UDamageHandlingComponent>(TEXT("DamageHandlingComp"));

	//Possession
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Orient To Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 300, 0);
}
 
// Called when the game starts or when spawned
void ABardPlayer::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance=GetMesh()->GetAnimInstance();
	//When Hit play animation
	this->OnTakeAnyDamage.AddDynamic(this, &ABardPlayer::PlayHitAnim);
	if(AnimInstance)
	AnimInstance->OnMontageEnded.AddDynamic(this,&ABardPlayer::WhenCompleted);
	
	//Enhanced Movement Input Context Init
	IgnoredActors.Add(this);
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
	//On Damage/Play Hit Animation
	
	//Input Actions
	if(EPI)
	{
		EPI->BindAction(Move, ETriggerEvent::Triggered, this, &ABardPlayer::Movement);
		EPI->BindAction(CombatAction, ETriggerEvent::Started, this, &ABardPlayer::CombatFunction);
		EPI->BindAction(CombatAction, ETriggerEvent::Triggered, this, &ABardPlayer::CombatFunctionChargeClock);
		EPI->BindAction(CombatAction, ETriggerEvent::Completed, this, &ABardPlayer::CombatFunctionRelease);
		EPI->BindAction(SwapWeapon, ETriggerEvent::Started, this, &ABardPlayer::Weaponswap);
	}
}
//Movement
void ABardPlayer::Movement(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();
	AddMovementInput(FVector(1,0,0), MovementValue.Y);
	AddMovementInput(FVector(0,1,0), MovementValue.X);
}

void ABardPlayer::CombatFunction()
{
	if(!IsDrumming)
	{
		if(!IsFluting)
		{
			if (WeaponNumber == 1)
			{
			if (FluteSlash)
			{
				UNiagaraComponent*Slash=UNiagaraFunctionLibrary::SpawnSystemAttached(FluteSlash,GetMesh(),"SlashSocket",GetMesh()->GetBoneLocation("SlashSocket"),FRotator::ZeroRotator,EAttachLocation::SnapToTargetIncludingScale,false);
				PlayAnimMontage(FluteAttack);
			
			if(!SpawnedFlute)
			{
				SpawnedFlute=GetWorld()->SpawnActor<AActor>(Flute, Position, FRotator(90,0,0));
				FluteRef=Cast<AWeaponBase>(SpawnedFlute);
			}
				FluteRef->FluteCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				IsFluting=true;
				SpawnedFlute->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("FluteSocket"));
			
			}
		}
		if (WeaponNumber == 2)
		{
		IsDrumming = true;
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		GetWorldTimerManager().SetTimer(Handle, this, &ABardPlayer::ActivateMovement,1.f,false,2.f);
		GetWorldTimerManager().SetTimer(DrumAOEHandle, this, &ABardPlayer::SpawnDrumAOE,1.f,false,1.2);
		PlayAnimMontage(DrumAttack);
		if (SpawnedFlute)
		{
			SpawnedFlute->Destroy();
			SpawnedFlute = nullptr;
		}
			
		/*LineTraceStart = GetActorLocation() + GetActorForwardVector() * FVector(100, 0, 0);*/
		LineTraceStart = DrumSpawn->GetComponentLocation();
		LineTraceEnd = LineTraceStart + FVector(0, 0, -300);

		bool HitSomething=GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility);
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red,false, 2.f);
		
		if(HitSomething)
		{
			if(!SpawnedDrum)
				SpawnedDrum = GetWorld()->SpawnActor<AActor>(Drum, FVector(Hit.Location), GetCharacterMovement()->GetLastUpdateRotation());
		}
		else { GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "Failed"); }
			DrumStick1 = GetWorld()->SpawnActor<AActor>(DrumStick_BP,Position,FRotator::ZeroRotator);
			DrumStick2 = GetWorld()->SpawnActor<AActor>(DrumStick_BP,Position,FRotator::ZeroRotator);
			DrumStick1->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"DrumStickL");
			DrumStick2->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"DrumStickR");
			
	}
		if (WeaponNumber==3)
		{
		//PlayAnimMontage(HarpAttack);
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, "Harp");
		}
		}
		
	}
	
}
void ABardPlayer::CombatFunctionChargeClock()
{
	TimeSpent += GetWorld()->DeltaTimeSeconds;
}

void ABardPlayer::CombatFunctionRelease()
{
	if(WeaponNumber==3)
	{
		if(TimeSpent < 1 && TimeSpent > 0)
		{
			GEngine->AddOnScreenDebugMessage(0,1,FColor::Red, TEXT("1 Damage"));
			//GetWorld()->SpawnActor<AArrow>(Arrow, GetActorLocation()+FVector(100,0,0), FRotator(GetActorRotation().Yaw));
		}
		if(TimeSpent < 2 && TimeSpent > 1)
		{
			GEngine->AddOnScreenDebugMessage(0,1,FColor::Red, TEXT("2 Damage"));
			//GetWorld()->SpawnActor<AArrow>(Arrow, GetActorLocation()+FVector(100,0,0), FRotator(GetActorRotation().Yaw));
		}
		if(TimeSpent > 2)
		{
			GEngine->AddOnScreenDebugMessage(0,1,FColor::Red, TEXT("3 Damage"));
			//GetWorld()->SpawnActor<AArrow>(Arrow, GetActorLocation()+FVector(100,0,0), FRotator(GetActorRotation().Yaw));
		}
		TimeSpent = 0;
	}
}

void ABardPlayer::DoDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass)
{

}

void ABardPlayer::ActivateMovement()
{
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	IsDrumming = false;
	SpawnedDrum = nullptr;
	GetWorldTimerManager().ClearTimer(Handle);
}

void ABardPlayer::PlayHitAnim(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	PlayAnimMontage(HitAnim);
}

void ABardPlayer::WhenCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	if(!bInterrupted)
	{
		if(Montage==FluteAttack)
		{
			FluteRef->FluteCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			IsFluting=false;
			
		}
		if(Montage==DrumAttack&&Montage!=HitAnim)
		{
			DrumStick1->Destroy();
			DrumStick2->Destroy();
		}
	}
	else
	{
		if(Montage==FluteAttack)
		{
			FluteRef->FluteCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			IsFluting=false;
		}
	}
}

void ABardPlayer::SpawnDrumAOE()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DrumAOE, Hit.Location+FVector(0,0,1));
	if (SpawnedDrum)
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 1.f, DrumSpawn->GetComponentLocation(), 500.f, BaseDamageType, IgnoredActors);
}

void ABardPlayer::Weaponswap()
{
	if(!IsDrumming)
{
	if(!IsFluting)
	WeaponNumber++;
}
	if (WeaponNumber > 3)
    		WeaponNumber = 1;
}

