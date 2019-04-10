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

	FVector Location(0.f, 0.f, 0.f);
	FRotator Rotation(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;

	AEndlessRunnerFloor* Floor = GetWorld()->SpawnActor<AEndlessRunnerFloor>(Location, Rotation, SpawnInfo);
	NextSpawnLocation = Floor->GetAttachTransform();
}

void AEndlessRunnerGameModeBase::CreateFloorTile()
{
	//TODO:
	//AEndlessRunnerFloor* Floor = GetWorld()->SpawnActor<AEndlessRunnerFloor>(GetClass(), NextSpawnLocation);
	//NextSpawnLocation = Floor->GetAttachTransform();
}
