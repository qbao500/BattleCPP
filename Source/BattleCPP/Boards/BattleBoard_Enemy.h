// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleBoard.h"
#include "BattleBoard_Enemy.generated.h"

class ABattleBoard_Player;

UCLASS()
class BATTLECPP_API ABattleBoard_Enemy : public ABattleBoard
{
	GENERATED_BODY()

public:
	ABattleBoard_Enemy():ABattleBoard()
	{
		bIsPlayer = false;
	}

	void EnemyAttack(ABattleBoard_Player* PlayerRef);

private:
	UPROPERTY(VisibleInstanceOnly)
	bool bIsSearching = false;

	UPROPERTY(VisibleInstanceOnly)
	bool bShouldSearchNew = false;

	int32 AttackRow;
	int32 AttackColumn;

	UPROPERTY(VisibleInstanceOnly)
	FVector2D AttackDirection;

	UPROPERTY()
	class APlaneTile* PickedTile;

	UPROPERTY()
	class APlaneTile* SearchingTile;

	UPROPERTY(VisibleInstanceOnly)
	class APlaneTile* LastHitTile;

	UPROPERTY(VisibleInstanceOnly)
	TArray<APlaneTile*> PossibleTiles;

	UFUNCTION()
	void RandomAttack(ABattleBoard_Player* PlayerRef);

	UFUNCTION()
	void SearchingAttack(ABattleBoard_Player* PlayerRef);

	UFUNCTION()
    void ForwardAttack(ABattleBoard_Player* PlayerRef);
	
	UFUNCTION()
	void AddPossibleTiles(ABattleBoard_Player* PlayerRef);

	UFUNCTION()
	void CheckValidTile(APlaneTile* TileToCheck);

	UFUNCTION()
	void ChangeState(bool bShouldGoSearch); 
};

