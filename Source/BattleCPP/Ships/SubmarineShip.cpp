// Fill out your copyright notice in the Description page of Project Settings.


#include "SubmarineShip.h"

#include "../Enums/TileTypeEnum.h"

USubmarineShip::USubmarineShip()
{
	TileType = ETileType::Submarine;
	Length = 3;
}

USubmarineShip::~USubmarineShip()
{
}
