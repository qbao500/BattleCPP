// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMasterShip.generated.h"

enum class ETileType : uint8;
/**
 * 
 */
UCLASS()
class BATTLECPP_API UMasterShip: public UObject
{
	GENERATED_BODY()
	
public:
	UMasterShip();

	ETileType TileType;

	int32 Length;
	int32 HitCount = 0;

	void GetShot();
	bool IsDestroyed();
};
