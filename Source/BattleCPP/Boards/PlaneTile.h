// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Structs/CoordinateStruct.h"
#include "../Enums/TileTypeEnum.h"
#include "GameFramework/Actor.h"
#include "PlaneTile.generated.h"

UCLASS()
class BATTLECPP_API APlaneTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneTile();

	UPROPERTY()
	class ABattleBoard* MotherBoard;

	UPROPERTY()
	class UMasterShip* CurrentShip;
	
	UPROPERTY(VisibleInstanceOnly)
	FCoordinateStruct Coordinate;
	
	UPROPERTY(VisibleInstanceOnly)
	ETileType TileType;

	UPROPERTY(VisibleInstanceOnly)
	bool bIsPlayer;	// Player board will not receive mouse events
	
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlaneMesh;
	
	UPROPERTY()
	class ABattleCPPGameModeBase* GameModeRef;

	// Materials
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* NormalMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* HoverMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* ShipMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* HitMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Mouse events
	UFUNCTION()
    void MouseHoverBegin(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
    void MouseHoverEnd(UPrimitiveComponent* TouchedComponent);	
	UFUNCTION()
    void MouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	UFUNCTION()
	bool IsFree() const;

	UFUNCTION()
    bool IsHit() const;

	UFUNCTION()
    bool IsMissed() const;

	UFUNCTION()
    bool CanBeShot() const;

	UFUNCTION()
	bool NotInteractable() const;

	UFUNCTION()
	void GetHit();

	UFUNCTION()
	void ShipPlaced(ETileType ShipType, UMasterShip* ShipRef);

	UFUNCTION()
	bool CheckHit();
};
