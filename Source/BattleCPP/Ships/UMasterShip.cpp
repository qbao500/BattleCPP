// Fill out your copyright notice in the Description page of Project Settings.


#include "UMasterShip.h"

UMasterShip::UMasterShip()
{
}

void UMasterShip::GetShot()
{
	HitCount++;
}

bool UMasterShip::IsDestroyed()
{
	// If the ship get shot equal to its length, it is destroyed
	return HitCount >= Length;
}
