// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMasterShip.h"

#include "BattleShip.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECPP_API UBattleShip: public UMasterShip
{
	GENERATED_BODY()
	
public:
	UBattleShip();
	~UBattleShip();
};
