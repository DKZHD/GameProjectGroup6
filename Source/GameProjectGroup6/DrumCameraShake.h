// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "DrumCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UDrumCameraShake : public UCameraShakeBase
{
	GENERATED_BODY()
public:
	void UCameraShakeBase(const FObjectInitializer& ObjectInitializer);
	UPROPERTY()
	class UCameraShakeBase* CameraShakeBase;
	UPROPERTY()
	UCameraShakePattern* Perlin;
};
