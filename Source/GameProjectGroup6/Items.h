// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UDamageHandlingComponent;
class ABardPlayer;

UCLASS()
class GAMEPROJECTGROUP6_API AItems : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Sets default values for this actor's properties
	AItems();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Mesh Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USkeletalMeshComponent* StaticMesh;

	//Collusion Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USphereComponent* Collider;

	//Damage Handling Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UDamageHandlingComponent* DamageHandling;

	//Bard Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ABardPlayer* Bard;


	//On overlap function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComponent,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	//How often enemies drop healing item
	int Droprate;
};
