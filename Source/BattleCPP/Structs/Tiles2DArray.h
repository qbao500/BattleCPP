// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Boards/PlaneTile.h"
#include "Tiles2DArray.generated.h"

USTRUCT(BlueprintType)
struct FTiles2DArray
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<APlaneTile*> TileArray;

	// To show as 2D array: Tile[Row][Column]
	APlaneTile* operator[] (const int32 Index)
	{
		return TileArray[Index];
	}

	void Add(APlaneTile* Tile)
	{
		TileArray.Add(Tile);
	}
};

