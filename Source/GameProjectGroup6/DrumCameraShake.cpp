// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumCameraShake.h"


void UDrumCameraShake::UCameraShakeBase(const FObjectInitializer& ObjectInitializer)
{
	CameraShakeBase=CreateDefaultSubobject<class UCameraShakeBase>(TEXT("CameraShake"));
	CameraShakeBase->SetRootShakePattern(Perlin);
	this->bSingleInstance=true;
}
