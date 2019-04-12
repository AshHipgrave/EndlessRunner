// Fill out your copyright notice in the Description page of Project Settings.

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

private:
	FVector NextSpawnLocation = FVector::ZeroVector;
};
