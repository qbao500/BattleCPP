// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyerShip.h"

#include "../Enums/TileTypeEnum.h"

UDestroyerShip::UDestroyerShip()
{
	TileType = ETileType::Destroyer;
	Length = 2;
}

UDestroyerShip::~UDestroyerShip()
{
}
