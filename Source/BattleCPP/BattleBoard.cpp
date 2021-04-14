// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBoard.h"

#include "BattleCPPGameModeBase.h"
#include "BattleShip.h"
#include "CarrierShip.h"
#include "CruiserShip.h"
#include "DestroyerShip.h"
#include "SubmarineShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleBoard::ABattleBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABattleBoard::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnTiles();
	PlaceShipsRandomly();
}

void ABattleBoard::ShipDestroyed()
{
	ShipAmount--;
	if (ShipAmount <= 0)
	{
		// Tell GameMode to end game
		Cast<ABattleCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameEnded();
	}
}

void ABattleBoard::SpawnTiles()
{
	InitializeRows();
	
	FVector Location = GetActorLocation();
	const float StartRow = Location.Y;
	
	for (int32 Row = 0; Row < BoardRow; Row++)
	{		
		for (int32 Column = 0; Column < BoardColumn; Column++)
		{
		    // First tile is at board original location			
			APlaneTile* Tile = GetWorld()->SpawnActor<APlaneTile>(TileClass, Location, FRotator(0,0,0));
			Tile->bIsPlayer = bIsPlayer;
			Tile->MotherBoard = this;
			
			// Add column to row
			Tiles[Row].Add(Tile);

			// Set Coordinate
			Tile->Coordinate.Row = Row;
			Tile->Coordinate.Column = Column;			

			// Go right
			Location.Y += 100;

			// Reset when reach max
			if (Column >= (BoardColumn - 1)) Location.Y = StartRow;			
		}

		// Go down
		Location.X -= 100;		
	}	
}

void ABattleBoard::InitializeRows()
{
	// Row (and Column) will be from 0 to 9 if board is 10x10
	for (int32 Row = 0; Row < BoardRow; Row++)
	{
		Tiles.Add(FTiles2DArray());
	}
}

void ABattleBoard::InitializeShips()
{	
	// From largest to smallest size, would be less likely to re-calculate
	// If you need to add more ship (which is inherited from UMasterShip), just add here, or remove
	Ships.AddUnique(NewObject<UCarrierShip>());
	Ships.AddUnique(NewObject<UBattleShip>());
	Ships.AddUnique(NewObject<UCruiserShip>());
	Ships.AddUnique(NewObject<USubmarineShip>());
	Ships.AddUnique(NewObject<UDestroyerShip>());
	
	ShipAmount = Ships.Num();
}

void ABattleBoard::PlaceShipsRandomly()
{
	InitializeShips();

	for (auto Ship: Ships)
	{
		CalculateShipTiles(Ship);
	}
}

void ABattleBoard::CalculateShipTiles(UMasterShip* Ship)
{
	// Pick random row and column start point
	const int32 StartRow = FMath::RandRange(0, BoardRow - 1);
	int32 EndRow = StartRow;
	const int32 StartColumn = FMath::RandRange(0, BoardColumn - 1);
	int32 EndColumn = StartColumn;

	// Random direction, if = 0: move down with rows, otherwise: move right with columns
	const int32 Direction = FMath::RandRange(0, 101) % 2;
	if (Direction == 0)
	{
		for (int32 i = 1; i < Ship->Length; i++)
		{
			EndRow++;
		}
	}
	else
	{
		for (int32 i = 1; i < Ship->Length; i++)
		{
			EndColumn++;
		}
	}

	// If exceed board's size, re-calculate
	if (EndRow > (BoardRow - 1) || EndColumn > (BoardColumn - 1))
	{
		CalculateShipTiles(Ship);
		return;
	}

	// Pick tiles based on direction
	TArray<APlaneTile*> PickedTiles;
	if (Direction == 0)
	{
		for (int32 Row = StartRow; Row <= EndRow; Row++)
		{
			PickedTiles.AddUnique(Tiles[Row][StartColumn]);
		}
	}
	else
	{
		for (int32 Column = StartColumn; Column <= EndColumn; Column++)
		{
			PickedTiles.AddUnique(Tiles[StartRow][Column]);			
		}
	}

	// Check if all picked tiles are free
	for (auto Tile: PickedTiles)
	{
		// If the tile is not free, re-calculate
		if (!Tile->IsFree())
		{
			CalculateShipTiles(Ship);
			return;
		}
	}

	// If everything passed, place ship on tiles
	for (auto Tile: PickedTiles)
	{
		Tile->ShipPlaced(Ship->TileType, Ship);
	}
}

