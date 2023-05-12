// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BardGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UBardGameInstance : public UGameInstance
{
	GENERATED_BODY()
	virtual void StartGameInstance() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenu_BP;
public:
	
	UPROPERTY()
	bool HasSpawnedMainMenu=false;
	
	UPROPERTY()
	bool CheckedBox=false;
	
	UPROPERTY()
	FString WindowState;
	
};
