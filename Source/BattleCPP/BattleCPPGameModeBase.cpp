// Copyright Epic Games, Inc. All Rights Reserved.


#include "BattleCPPGameModeBase.h"

#include "Boards/BattleBoard_Player.h"
#include "Boards/BattleBoard_Enemy.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABattleCPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ModifyController();

	SpawnBoards();
}

void ABattleCPPGameModeBase::ModifyController()
{
	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
}

void ABattleCPPGameModeBase::SpawnBoards()
{
	const FRotator Rotation = FRotator(0, 0, 0);
	PlayerRef = GetWorld()->SpawnActor<ABattleBoard_Player>(PlayerBoard, FVector(0, -1100, 0), Rotation);
	EnemyRef = GetWorld()->SpawnActor<ABattleBoard_Enemy>(EnemyBoard, FVector(0, 1100, 0), Rotation);
}

void ABattleCPPGameModeBase::EnemyTurn()
{
	Controller->bShowMouseCursor = false;
	
	EnemyRef->EnemyAttack(PlayerRef);

	Controller->bShowMouseCursor = true;
}

void ABattleCPPGameModeBase::GameEnded()
{
	SetPause(Controller);

	// Re-check who win
	if (EnemyRef->ShipAmount <= 0) bIsPlayerWon = true;
	else if (PlayerRef->ShipAmount <= 0) bIsPlayerWon = false;

	auto Widget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	Widget->AddToViewport();
}
