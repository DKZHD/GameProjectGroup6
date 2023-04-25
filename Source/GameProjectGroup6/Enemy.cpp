	// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "DamageHandlingComponent.h"
#include "EnemyActorComponent.h"
#include "HealthBardComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthBardComponent.h"
#include "Components/SceneComponent.h"

	// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageHandling = CreateDefaultSubobject<UDamageHandlingComponent>("DamageHandling");
	DamageHandling->DefaultHealth = 3;
	DamageHandling->Health = DamageHandling->DefaultHealth;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->GravityScale = 3.f;
	this->OnTakeRadialDamage.AddDynamic(this, &AEnemy::OnRadialDamage);
	
	HealthBarWidget = CreateDefaultSubobject<UHealthBardComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	this->OnTakeRadialDamage.AddDynamic(this, &AEnemy::OnRadialDamage);
	AutoPossessAI= EAutoPossessAI::PlacedInWorldOrSpawned;
	
	DamageHandling->Health = DamageHandling->DefaultHealth;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(DamageHandling->IsDead)
	{
		Die();
	}
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

	void AEnemy::OnRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "Yay!");
	this->LaunchCharacter(FVector(0, 0, 750.f), true, false);
	IsStunned = true;
	CanAttack = false;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemy::ResetStun, 1, false, 4.f);
	GetWorldTimerManager().SetTimer(GravityHandle, this, &AEnemy::ChangeMovementMode, 1, false, .6);
}
void AEnemy::ChangeMovementMode()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetWorldTimerManager().ClearTimer(GravityHandle);
}

void AEnemy::ResetStun()
{
	IsStunned = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetWorldTimerManager().ClearTimer(Handle);
}

void AEnemy::Die()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Dead");
	DamageHandling->IsDead = false;
}


