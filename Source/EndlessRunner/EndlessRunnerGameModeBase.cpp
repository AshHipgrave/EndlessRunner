// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunnerGameModeBase.h"
#include "RunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EndlessRunnerFloor.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_RunnerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 5; i++)
		CreateFloorTile();
}

void AEndlessRunnerGameModeBase::CreateFloorTile()
{
	AEndlessRunnerFloor* FloorTile = GetWorld()->SpawnActor<AEndlessRunnerFloor>(NextSpawnLocation, FRotator::ZeroRotator);
	NextSpawnLocation = FloorTile->GetAttachLocation();
}
