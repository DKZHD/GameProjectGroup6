// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"
#include "BardPlayer.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageHandlingComponent.h"

// Sets default values
AItems::AItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();

	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Collider -> OnComponentBeginOverlap.AddDynamic(this, &AItems::OnOverlapBegin);
}


// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItems::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Bard)
	{
		if(OtherActor->IsA<ABardPlayer>())
		{
			GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Magenta,"Collide");

			if(Bard->DamageHandlingComponent->Health < 5)
			{
				FMath::Clamp(Bard->DamageHandlingComponent->Health +=1, 0, 5);
				this -> Destroy();
			}
		}
	}
}

