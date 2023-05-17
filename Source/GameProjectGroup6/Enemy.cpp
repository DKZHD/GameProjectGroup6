	// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "DamageHandlingComponent.h"
#include "HealthBardComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Items.h"
#include "Kismet/GameplayStatics.h"
#include "BardPlayer.h"
#include "Components/SphereComponent.h"
#include "EnemyAIController.h"
#include "Arrow.h"
#include "Kismet/KismetMathLibrary.h"



	// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets up the damage handling component
	DamageHandling = CreateDefaultSubobject<UDamageHandlingComponent>("DamageHandling");
	DamageHandling->DefaultHealth = 3;
	DamageHandling->Health = DamageHandling->DefaultHealth;

	//Sets up movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->GravityScale = 3.f;

	//Initiates On take radial damage
	this->OnTakeRadialDamage.AddDynamic(this, &AEnemy::OnRadialDamage);

	//Binds the health bar widget to the enemy
	HealthBarWidget = CreateDefaultSubobject<UHealthBardComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	//Initiates the collider
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetMesh(),"ColliderSocket");
	Collider->SetCollisionProfileName("OverlapOnlyPawn");
	Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItHit = true;

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	Bow->SetupAttachment(GetMesh(), "BowSocket");
	CanShoot = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
	

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	this->OnTakeRadialDamage.AddDynamic(this, &AEnemy::OnRadialDamage);
	this->OnTakeAnyDamage.AddDynamic(this,&AEnemy::OnAnyDamageTaken);
	
	//Sets Enemy Health to Default Health
	DamageHandling->Health = DamageHandling->DefaultHealth;

	//Cast to bard player
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Bind the OnOverlapBegin function
	Collider -> OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	
	//Initialize AnimNotify
	AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AEnemy::AnimNotifyBegin);
		AnimInstance->OnMontageEnded.AddDynamic(this,&AEnemy::WhenCompleted);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	// Checks DamageHandling to see if Enemy is dead
	if(DamageHandling->IsDead)
	{
		Die();
	}
	// Sets percentage on health bar
	if(DamageHandling && HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(DamageHandling->GetHealthPercent());
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// When actor take radial damage
void AEnemy::OnRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "Yay!");
	this->LaunchCharacter(FVector(0, 0, 750.f), true, false);
	IsStunned = true;
	CanAttack = false;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemy::ResetStun, 1, false, 3.f);
	GetWorldTimerManager().SetTimer(GravityHandle, this, &AEnemy::ChangeMovementMode, 1, false, .6);
}

void AEnemy::OnAnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UGameplayStatics::PlaySound2D(GetWorld(),DamageSound,1,1);
	PlayAnimMontage(GoblinHit);
}

// Change movement mode to none
void AEnemy::ChangeMovementMode()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetWorldTimerManager().ClearTimer(GravityHandle);
}

	// Reset stun, timer and movement mode
void AEnemy::ResetStun()
{
	IsStunned = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetWorldTimerManager().ClearTimer(Handle);
}

// Going to run death animation and destroy the actor
void AEnemy::Die()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Dead");
	this->Destroy();

	Droprate = FMath::RandRange(1,2);
	if(Droprate == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Dropped");
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator(0.f, -90.f, 0.f);
		GetWorld()->SpawnActor<AActor>(ItemsToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

	void AEnemy::TakenOver()
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}

void AEnemy::AttackFunction()
{
	PlayAnimMontage(HitMontage);
}

void AEnemy::BowAttackFunction()
{
	if(CanShoot && !IsStunned)
	{
		PlayAnimMontage(BowMontage);
		CanShoot = false;
	}
}
void AEnemy::WhenCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	CanShoot = true;
}

	//Check for overlap
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if Bard cast worked
	
	//Check if the overlapping component is the bard player
	if(OtherActor->IsA<ABardPlayer>() && !ItHit)
	{
		//Applies damage to bard player
		UGameplayStatics::ApplyDamage(OtherActor, 1, this->GetController(), this, UDamageType::StaticClass());
		ItHit = true;
	}
}

void AEnemy::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if(NotifyName=="Start")
	{
		Collider->SetCollisionProfileName("OverlapAllDynamic");
		ItHit = false;
	}
	if(NotifyName=="End")
	{
		Collider->SetCollisionProfileName("NoCollision");
	}
	if(NotifyName=="Shoot")
    {
        FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Bard->GetActorLocation());
        ArrowRef = GetWorld()->SpawnActor<AArrow>(Arrow, GetActorLocation()+FVector(75,0,0), FRotator(0,Rotation.Yaw,0));
    }
	if(NotifyName=="ShootEnd")
	{
		CanShoot = true;
	}
}

	




