// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneTile.h"


#include "BattleBoard.h"
#include "../BattleCPPGameModeBase.h"
#include "../Ships/UMasterShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlaneTile::APlaneTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	SetRootComponent(PlaneMesh);
	PlaneMesh->SetMaterial(0, NormalMaterial);
}

// Called when the game starts or when spawned
void APlaneTile::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ABattleCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	PlaneMesh->OnBeginCursorOver.AddDynamic(this, &APlaneTile::MouseHoverBegin);
	PlaneMesh->OnEndCursorOver.AddDynamic(this, &APlaneTile::MouseHoverEnd);
	PlaneMesh->OnReleased.AddDynamic(this, &APlaneTile::MouseReleased);
}

void APlaneTile::MouseHoverBegin(UPrimitiveComponent* TouchedComponent)
{
	if (NotInteractable()) return;

	PlaneMesh->SetMaterial(0, HoverMaterial);
}

void APlaneTile::MouseHoverEnd(UPrimitiveComponent* TouchedComponent)
{
	if (NotInteractable()) return;
	
	PlaneMesh->SetMaterial(0, NormalMaterial);
}

void APlaneTile::MouseReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (NotInteractable()) return;
	
	CheckHit();
	
	GameModeRef->EnemyTurn();
}

bool APlaneTile::IsFree() const
{
	return TileType == ETileType::Free;
}

bool APlaneTile::IsHit() const
{
	return TileType == ETileType::Hit;
}

bool APlaneTile::IsMissed() const
{
	return TileType == ETileType::Miss;
}

bool APlaneTile::CanBeShot() const
{
	return !IsHit() && !IsMissed();
}

bool APlaneTile::NotInteractable() const
{
	return bIsPlayer || IsHit() || IsMissed();
}

void APlaneTile::GetHit()
{
	TileType = ETileType::Hit;
	PlaneMesh->SetMaterial(0, HitMaterial);
	
	CurrentShip->GetShot();
	if (CurrentShip->IsDestroyed())
	{
		MotherBoard->ShipDestroyed();
	}
}

void APlaneTile::ShipPlaced(ETileType ShipType, UMasterShip* ShipRef)
{
	TileType = ShipType;
	CurrentShip = ShipRef;
	
	// Show player's ships
	if (bIsPlayer)
	{
		PlaneMesh->SetMaterial(0, ShipMaterial);
	}
}

bool APlaneTile::CheckHit()
{
	if (!IsFree() && CurrentShip && CanBeShot())
	{
		GetHit();
		return true;
	}

	// Otherwise missed
	TileType = ETileType::Miss;
	SetActorHiddenInGame(true);
	return false;
}
