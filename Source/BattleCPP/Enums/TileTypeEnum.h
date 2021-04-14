// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETileType: uint8
{
	Free,		// Default
	Hit,
	Miss,
	Destroyer,	// 2
	Submarine,	// 3
	Cruiser,	// 3
	Battleship,	// 4
	Carrier		// 5
};
