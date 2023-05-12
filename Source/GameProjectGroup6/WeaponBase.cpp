// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "BardPlayer.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	FluteCollision=CreateDefaultSubobject<UBoxComponent>(TEXT("FLuteCollision"));
	FluteCollision->SetupAttachment(Mesh);
	FluteCollision->Deactivate();
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FluteCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlap);
	FluteCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// When flute is overlapping
void AWeaponBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA<AEnemy>())
	{
		Enemy=Cast<AEnemy>(OtherActor);
		if(OtherComp==Enemy->GetCapsuleComponent())
		{
			UGameplayStatics::ApplyDamage(OtherActor,.5,UGameplayStatics::GetPlayerController(GetWorld(),0),this,BaseDamage);
			GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Magenta,"It weeee Hit!");
		}
	}
}

