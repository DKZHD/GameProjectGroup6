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

	//Initialize the StaticMesh
	StaticMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	//Initialize the Collider
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();

	//Cast to bard player
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Bind the OnOverlapBegin function
	Collider -> OnComponentBeginOverlap.AddDynamic(this, &AItems::OnOverlapBegin);
}


// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItems::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if Bard cast worked
	if(Bard)
	{
		//Check if the overlapping component is the bard player
		if(OtherActor->IsA<ABardPlayer>())
		{
			//Check if the bard player's health is less than 5
			if(Bard->DamageHandlingComponent->Health < 5)
			{
				//Add 1 to the bard player's health
				FMath::Clamp(Bard->DamageHandlingComponent->Health +=1, 0, 5);
				//Destroy the item
				this -> Destroy();
			}
		}
	}
}

