// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items.generated.h"

UCLASS()
class GAMEPROJECTGROUP6_API AItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItems();


	//Mesh Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class USkeletalMeshComponent* StaticMesh;

	//Collusion Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class USphereComponent* Collider;

	//Damage Handling Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class UDamageHandlingComponent* DamageHandling;

	//Bard Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class ABardPlayer* Bard;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//On overlap function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComponent,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	//How often enemies drop healing item
	int Droprate;
};
