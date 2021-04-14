// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMasterShip.h"
#include "PlaneTile.h"
#include "Tiles2DArray.h"
#include "GameFramework/Actor.h"
#include "BattleBoard.generated.h"

UCLASS()
class BATTLECPP_API ABattleBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleBoard();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlaneTile> TileClass;

	UPROPERTY(VisibleAnywhere)
	bool bIsPlayer;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UMasterShip*> Ships;
	
public:
	UPROPERTY(EditDefaultsOnly)
	int32 BoardRow = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 BoardColumn = 10;

	// Array in array = 2D Array
	UPROPERTY(VisibleInstanceOnly,  BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<FTiles2DArray> Tiles;

	UPROPERTY(VisibleInstanceOnly)
	int32 ShipAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void ShipDestroyed();

private:
	UFUNCTION()
	void SpawnTiles();

	UFUNCTION()
	void InitializeRows();
	
	UFUNCTION()
	void InitializeShips();

	UFUNCTION()
	void PlaceShipsRandomly();

	UFUNCTION()
	void CalculateShipTiles(UMasterShip* Ship);
	
};
