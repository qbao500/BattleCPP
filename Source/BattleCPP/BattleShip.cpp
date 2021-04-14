// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleShip.h"

#include "TileTypeEnum.h"

UBattleShip::UBattleShip()
{
	TileType = ETileType::Battleship;
	Length = 4;
}

UBattleShip::~UBattleShip()
{
}
