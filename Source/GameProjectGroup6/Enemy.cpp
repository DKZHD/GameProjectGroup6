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
	Collider->SetCollisionProfileName("IgnoreOnlyPawn");

	AutoPossessAI= EAutoPossessAI::PlacedInWorldOrSpawned;
}
	

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	this->OnTakeRadialDamage.AddDynamic(this, &AEnemy::OnRadialDamage);
	
	//Sets Enemy Health to Default Health
	DamageHandling->Health = DamageHandling->DefaultHealth;

	//Cast to bard player
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Bind the OnOverlapBegin function
	Collider -> OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Checks if enemy is attacking and sets the collision
	 if(CanAttack)
	 {
	 	Collider ->SetCollisionProfileName("OverlapOnlyPawn");
	 }
	 if(!CanAttack)
	 {
	 	Collider ->SetCollisionProfileName("IgnoreOnlyPawn");
	 }

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
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemy::ResetStun, 1, false, 4.f);
	GetWorldTimerManager().SetTimer(GravityHandle, this, &AEnemy::ChangeMovementMode, 1, false, .6);
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


	//Check for overlap
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if Bard cast worked
	if(Bard)
	{
		//Check if the overlapping component is the bard player
		if(OtherActor->IsA<ABardPlayer>())
		{
			GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Magenta,"Player Hit!");

			//Applies damage to bard player
			UGameplayStatics::ApplyDamage(Bard, 1, this->GetController(), this, UDamageType::StaticClass());
			
		}
	}
}


