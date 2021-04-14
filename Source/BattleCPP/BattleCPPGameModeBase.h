// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BattleBoard.h"
#include "GameFramework/GameModeBase.h"
#include "BattleCPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECPP_API ABattleCPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsPlayerWon;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABattleBoard> PlayerBoard;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABattleBoard> EnemyBoard;

	UPROPERTY()
	class ABattleBoard_Player* PlayerRef;

	UPROPERTY()
	class ABattleBoard_Enemy* EnemyRef;

	UPROPERTY()
	class APlayerController* Controller;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
protected:
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ModifyController();

	UFUNCTION()
	void SpawnBoards();

public:
	void EnemyTurn();

	void GameEnded();
};
