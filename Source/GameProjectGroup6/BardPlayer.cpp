// Fill out your copyright notice in the Description page of Project Settings.

#include "BardPlayer.h"

#include "Arrow.h"
#include "CustomHUD.h"
#include "DamageHandlingComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponBase.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "UI.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABardPlayer::ABardPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 900.f;
	SpringArm->AddRelativeRotation(FRotator(-45.f, 25.f, 0.f));
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	bUseControllerRotationYaw = false;

	DrumSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("DrumSpawn"));
	DrumSpawn->SetupAttachment(GetRootComponent());
	HarpSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("HarpSpawn"));
	HarpSpawn->SetupAttachment(GetRootComponent());

	DamageHandlingComponent = CreateDefaultSubobject<UDamageHandlingComponent>(TEXT("DamageHandlingComp"));
	DamageHandlingComponent->Health=5;
	
	//Possession
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Orient To Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400, 0);
}
 
// Called when the game starts or when spawned
void ABardPlayer::BeginPlay()
{
	Super::BeginPlay();
	CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	AnimInstance=GetMesh()->GetAnimInstance();
	CameraManager=UGameplayStatics::GetPlayerCameraManager(this,0);
	
	//When Hit play animation
	this->OnTakeAnyDamage.AddDynamic(this, &ABardPlayer::PlayHitAnim);
	
	if(AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this,&ABardPlayer::WhenCompleted);
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this,&ABardPlayer::AnimNotifyBegin);
	}
	
	
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

	if(IsDrumming)
		DrumCooldown-=DeltaTime;
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
		EPI->BindAction(Pause, ETriggerEvent::Started, this, &ABardPlayer::PauseFunction);
	}
}
//Movement
void ABardPlayer::Movement(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();
	if(!IsHarping)
	{
		AddMovementInput(FVector(1,0,0), MovementValue.Y);
		AddMovementInput(FVector(0,1,0), MovementValue.X);
	}
}

void ABardPlayer::ActivateMovement()
{
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	SpawnedDrum = nullptr;
	DrumCooldown=7;
	DrumAnimation=false;
	GetWorldTimerManager().ClearTimer(Handle);
	GetWorldTimerManager().SetTimer(Handle, this, &ABardPlayer::DrumAgain,1.f,false,7.f);
}

//Input Functions
void ABardPlayer::CombatFunction()
{
	if(!IsHarping)
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
        			if(!IsDrumming)
        			{
        				if (WeaponNumber == 2)
        				{
        					IsDrumming = true;
        					GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
        					GetWorldTimerManager().SetTimer(Handle, this, &ABardPlayer::ActivateMovement,1.f,false,2.f);
        					GetWorldTimerManager().SetTimer(DrumAOEHandle, this, &ABardPlayer::SpawnDrumAOE,1.f,false,1.2);
        					DrumAnimation=true;
        					PlayAnimMontage(DrumAttack);
        					if (SpawnedFlute)
        					{
        						SpawnedFlute->Destroy();
        						SpawnedFlute = nullptr;
        					}
        					LineTraceStart = DrumSpawn->GetComponentLocation();
        					LineTraceEnd = LineTraceStart + FVector(0, 0, -300);
                                
        					bool HitSomething=GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_Visibility);
                                		
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
        			}
        		
        		if (WeaponNumber==3)
        		{
        			if(SpawnedFlute)
        			{
        				SpawnedFlute->Destroy();
        				SpawnedFlute = nullptr;
        			}
        				SpawnedHarp=GetWorld()->SpawnActor<AActor>(Harp,HarpSpawn->GetComponentLocation(),GetCharacterMovement()->GetLastUpdateRotation());
        				if(SpawnedHarp)
        					PlayAnimMontage(HarpAttack,1);

        			}
        		}
	}
	
}
void ABardPlayer::CombatFunctionChargeClock()
{
	if(WeaponNumber==3)
	{
		TimeSpent += GetWorld()->DeltaTimeSeconds;
		if(TimeSpent < 2 && TimeSpent > 1&&!bHarpSound1)
		{
			UGameplayStatics::PlaySound2D(this,Harp1);
			bHarpSound1=true;
			
		}
		if(TimeSpent < 3 && TimeSpent > 2&&!bHarpSound2)
		{
			UGameplayStatics::PlaySound2D(this,Harp2);
			bHarpSound2=true;
		}
		if(TimeSpent > 3&&!bHarpSound3)
		{
			UGameplayStatics::PlaySound2D(this,Harp3);
			bHarpSound3=true;
		}
		ArrowRef=nullptr;
	}
	
}

void ABardPlayer::CombatFunctionRelease()
{
	if(WeaponNumber==3)
	{
		if(TimeSpent<1)
		{
			StopAnimMontage();
			if(SpawnedHarp)
			DespawnHarp();
		}
		if(TimeSpent < 2 && TimeSpent > 1)
		{
			UGameplayStatics::PlaySound2D(this, HarpReleased1);
			StopAnimMontage();
			PlayAnimMontage(HarpRelease);
			ArrowRef=GetWorld()->SpawnActor<AArrow>(Arrow,GetActorLocation()+FVector(75,0,0),GetCharacterMovement()->GetLastUpdateRotation());
			if(ArrowRef)
				ArrowRef->Damage=1.f;
		}
		if(TimeSpent < 3 && TimeSpent > 2)
		{
			UGameplayStatics::PlaySound2D(this, HarpReleased2);
			StopAnimMontage();
			PlayAnimMontage(HarpRelease);
			ArrowRef=GetWorld()->SpawnActor<AArrow>(Arrow,GetActorLocation()+FVector(75,0,0),GetCharacterMovement()->GetLastUpdateRotation());
			if(ArrowRef)
				ArrowRef->Damage=2.f;
		}
		if(TimeSpent > 3)
		{
			UGameplayStatics::PlaySound2D(this, HarpReleased3);
			StopAnimMontage();
			PlayAnimMontage(HarpRelease);
			ArrowRef=GetWorld()->SpawnActor<AArrow>(Arrow,GetActorLocation()+FVector(75,0,0),GetCharacterMovement()->GetLastUpdateRotation());
			if(ArrowRef)
				ArrowRef->Damage=3.f;
		}
		TimeSpent = 0;
		bHarpSound1=false;
		bHarpSound2=false;
		bHarpSound3=false;
	}
}

void ABardPlayer::Weaponswap()
{
	if(!DrumAnimation)
	{
		if(!IsFluting)
		{
			WeaponNumber++;
			UUI* UIref=Cast<UUI>(CustomHUD->UIWidget);
			UIref->ChangeUIPicture();
		}	
	}
	if (WeaponNumber > 3)
			WeaponNumber = 1;
}

void ABardPlayer::PauseFunction()
{
	CustomHUD->UIWidget->RemoveFromParent();
	PauseScreenRef=CreateWidget<UUserWidget>(GetWorld(),PauseScreen);
	PauseScreenRef->AddToViewport(0);
}


//Animation Functions
void ABardPlayer::PlayHitAnim(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(!IsHarping&&WeaponNumber!=3)
	{
		PlayAnimMontage(HitAnim);
	}
	
	if(DamageHandlingComponent->Health<=0)
	{
		if(CustomHUD)
		{
			CustomHUD->UIWidget->RemoveFromParent();
		}
		
		UUserWidget* Death=CreateWidget<UUserWidget>(GetWorld(),DeathScreen);
		Death->AddToViewport(0);
	}
}

void ABardPlayer::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	//FluteNotifies
	if(NotifyName=="1st")
		FluteRef->FluteCollision->SetCollisionProfileName("NoCollision");
	if(NotifyName=="2nd")
		FluteRef->FluteCollision->SetCollisionProfileName("OverlapAllDynamic");
	if(NotifyName=="Start")
		FluteRef->FluteCollision->SetCollisionProfileName("OverlapAllDynamic");
	if(NotifyName=="End")
		FluteRef->FluteCollision->SetCollisionProfileName("NoCollision");
	//DrumNotifies
	if(NotifyName=="Drum1")
		CameraManager->StartCameraShake(BP_DrumShake,.5);
	if(NotifyName=="Drum2")
		CameraManager->StartCameraShake(BP_DrumShake,.5);
	if(NotifyName=="Drum3")
		CameraManager->StartCameraShake(BP_DrumShake,3);
	//HarpNotifies
	if(NotifyName=="Freeze")
	{
		AnimInstance->Montage_SetPlayRate(HarpAttack,0);
	}
}

void ABardPlayer::WhenCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	if(!bInterrupted)
	{
		if(Montage==FluteAttack)
		{
			FluteRef->FluteCollision->SetCollisionProfileName("NoCollision");
			IsFluting=false;
		}
		if(Montage==DrumAttack&&Montage!=HitAnim)
		{
			DrumStick1->Destroy();
			DrumStick2->Destroy();
		}
		if(Montage==HarpAttack)
		{
			ArrowRef=nullptr;
			if(SpawnedHarp)
			DespawnHarp();
			IsHarping=false;
		}
	}
	else
	{
		if(Montage==FluteAttack)
		{
			FluteRef->FluteCollision->SetCollisionProfileName("NoCollision");
			IsFluting=false;
		}
		if(Montage==HarpAttack)
		{
			ArrowRef=nullptr;
			if(SpawnedHarp)
			DespawnHarp();
			IsHarping=false;
		}
	}
}

//Extra Functions
void ABardPlayer::SpawnDrumAOE()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DrumAOE, Hit.Location+FVector(0,0,1));
	
	if (SpawnedDrum)
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 1.f, DrumSpawn->GetComponentLocation(), 500.f, BaseDamageType, IgnoredActors);
}

void ABardPlayer::DespawnHarp()
{
	if(SpawnedHarp)
	SpawnedHarp->Destroy();
	SpawnedHarp=nullptr;
	GetWorldTimerManager().ClearTimer(Handle);
}

void ABardPlayer::DrumAgain()
{
	IsDrumming=false;
	DrumCooldown=0;
	GetWorldTimerManager().ClearTimer(Handle);
}



