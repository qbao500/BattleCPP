// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleBoard_Enemy.h"
#include "BattleBoard_Player.h"
#include "../Ships/UMasterShip.h"

void ABattleBoard_Enemy::EnemyAttack(ABattleBoard_Player* PlayerRef)
{
	if (bIsSearching)
	{
		SearchingAttack(PlayerRef);
	}
	else if (AttackDirection != FVector2D(0, 0))
	{
		ForwardAttack(PlayerRef);
	}
	else
	{
		RandomAttack(PlayerRef);
	}	
}

void ABattleBoard_Enemy::RandomAttack(ABattleBoard_Player* PlayerRef)
{
	// Pick random coordinate on Player Board
	AttackRow = FMath::RandRange(0, PlayerRef->BoardRow - 1);
	AttackColumn = FMath::RandRange(0, PlayerRef->BoardColumn - 1);
	PickedTile = PlayerRef->Tiles[AttackRow][AttackColumn];

	// If the tile cant be shot, find other place
	if (!PickedTile->CanBeShot())
	{
		RandomAttack(PlayerRef);
		return;
	}

	// Attack, then start searching if hit
	if (PickedTile->CheckHit())
	{
		bIsSearching = true;
		bShouldSearchNew = true;
		SearchingTile = PickedTile;
	}
}

void ABattleBoard_Enemy::SearchingAttack(ABattleBoard_Player* PlayerRef)
{
	// Search neighbors only when entering from RandomAttack
	if (bShouldSearchNew) AddPossibleTiles(PlayerRef);
	
	// If no neighbor tile can be attacked, switch to RandomAttack
	if (PossibleTiles.Num() == 0)
	{
		ChangeState(false);
		RandomAttack(PlayerRef);
		return;
	}
	
	// Pick random possibility
	PickedTile = PossibleTiles[FMath::RandRange(0, PossibleTiles.Num() - 1)];

	// Attack
	if (PickedTile->CheckHit())
	{
		// If ship is destroyed, return to RandomAttack
		if (PickedTile->CurrentShip->IsDestroyed())
		{
			ChangeState(false);
			return;
		}

		// Otherwise, start ForwardAttack that direction next turn
		bIsSearching = false;
		int32 X = PickedTile->Coordinate.Column - SearchingTile->Coordinate.Column;
		int32 Y = PickedTile->Coordinate.Row - SearchingTile->Coordinate.Row;
		AttackDirection = FVector2D(X, Y);
		LastHitTile = PickedTile;

		// And remove the path that's already attacked
		PossibleTiles.Remove(PickedTile);
	}
	else
	{
		// Remove missed possibility
		PossibleTiles.Remove(PickedTile);
		if (PossibleTiles.Num() == 0) bIsSearching = false;
	}
}

void ABattleBoard_Enemy::ForwardAttack(ABattleBoard_Player* PlayerRef)
{
	int32 PickedRow = LastHitTile->Coordinate.Row + AttackDirection.Y;
	int32 PickedColumn = LastHitTile->Coordinate.Column + AttackDirection.X;

	// If exceed size
	if (PickedRow < 0 || PickedRow >= PlayerRef->BoardRow || PickedColumn < 0 || PickedColumn >= PlayerRef->BoardColumn)
	{
		// Search again
		ChangeState(true);
		SearchingAttack(PlayerRef);
		return;
	}

	// Pick next tile
	PickedTile = PlayerRef->Tiles[PickedRow][PickedColumn];

	// If next tile cant be shot
	if (!PickedTile->CanBeShot())
	{
		// Search again
		ChangeState(true);
		SearchingAttack(PlayerRef);
		return;
	}

	// If hit, keep moving
	if (PickedTile->CheckHit())
	{
		LastHitTile = PickedTile;

		// If ship is destroyed, return to RandomAttack
		if (PickedTile->CurrentShip->IsDestroyed())
		{
			ChangeState(false);
			PossibleTiles.Empty();
		}
	}
	else
	{
		// If not hit, return to searching
		ChangeState(true);
	}
}

void ABattleBoard_Enemy::AddPossibleTiles(ABattleBoard_Player* PlayerRef)
{
	// Not always search
	bShouldSearchNew = false;

	// Refresh before adding new
	PossibleTiles.Empty();
	
	int32 PossibleRow = SearchingTile->Coordinate.Row;
	int32 PossibleColumn = SearchingTile->Coordinate.Column;
	APlaneTile* TempTile;

	// Maybe there's a more elegant way to do this, but remove item when iterating its array would crash the engine
	// These codes work fine for now
	// Up
	if (PossibleRow - 1 > 0)
	{
		TempTile = PlayerRef->Tiles[PossibleRow - 1][PossibleColumn];
		PossibleTiles.AddUnique(TempTile);
		CheckValidTile(TempTile);
	}		
	// Down
	if (PossibleRow + 1 <= PlayerRef->BoardRow - 1)
	{
		TempTile = PlayerRef->Tiles[PossibleRow + 1][PossibleColumn];
		PossibleTiles.AddUnique(TempTile);
		CheckValidTile(TempTile);
	}
	// Left
	if (PossibleColumn - 1 > 0)
	{
		TempTile = PlayerRef->Tiles[PossibleRow][PossibleColumn - 1];
		PossibleTiles.AddUnique(TempTile);
		CheckValidTile(TempTile);
	}
	// Right
	if (PossibleColumn + 1 <= PlayerRef->BoardColumn - 1)
	{
		TempTile = PlayerRef->Tiles[PossibleRow][PossibleColumn + 1];
		PossibleTiles.AddUnique(TempTile);
		CheckValidTile(TempTile);
	}
}

void ABattleBoard_Enemy::CheckValidTile(APlaneTile* TileToCheck)
{
	if (!TileToCheck->CanBeShot())
	{
		PossibleTiles.Remove(TileToCheck);
	}
}

void ABattleBoard_Enemy::ChangeState(bool bShouldGoSearch)
{
	bIsSearching = bShouldGoSearch;
	AttackDirection = FVector2D(0, 0);
}
