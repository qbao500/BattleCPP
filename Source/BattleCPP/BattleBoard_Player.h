// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleBoard.h"
#include "BattleBoard_Player.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECPP_API ABattleBoard_Player : public ABattleBoard
{
	GENERATED_BODY()
	
public:
	ABattleBoard_Player():ABattleBoard()
	{
		bIsPlayer = true;
	}
};
