// Copyright 2019 Ashley Hipgrave. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEndlessRunnerGameModeBase();

	virtual void BeginPlay() override;

	void CreateFloorTile();

	void NotifyPlayerObstacleCollision();

private:
	FVector NextSpawnLocation = FVector(300.0f, 0.0f, 0.0f);
};
