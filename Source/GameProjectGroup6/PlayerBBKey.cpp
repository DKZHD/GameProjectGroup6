// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBBKey.h"
#include "BardPlayer.h"

UPlayerBBKey::UPlayerBBKey()
{

}

void UPlayerBBKey::BeginPlay()
{
	Player= Cast<ABardPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}
