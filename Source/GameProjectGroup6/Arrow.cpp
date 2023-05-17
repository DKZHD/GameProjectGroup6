// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"

#include "Enemy.h"
#include "BardPlayer.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	SetRootComponent(Root);
	
	ArrowMesh=CreateDefaultSubobject<UStaticMeshComponent>("ArrowMesh");
	ArrowMesh->SetupAttachment(GetRootComponent());

	CollisionBox=CreateDefaultSubobject<UBoxComponent>("Collision");
	CollisionBox->SetupAttachment(ArrowMesh);

	Particle=CreateDefaultSubobject<UNiagaraComponent>("Trail");
	Particle->SetupAttachment(ArrowMesh);

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	ProjectileMovementComponent->InitialSpeed=2000.f;
	ProjectileMovementComponent->MaxSpeed=2000.f;
	ProjectileMovementComponent->ProjectileGravityScale=0;
	InitialLifeSpan=3.f;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AArrow::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrow::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AEnemy>())
	UGameplayStatics::ApplyDamage(OtherActor,Damage,UGameplayStatics::GetPlayerController(this,0),this,DamageType);

	if(OtherActor->IsA<ABardPlayer>())
		UGameplayStatics::ApplyDamage(OtherActor,Damage,EnemyController,this,DamageType);
}

