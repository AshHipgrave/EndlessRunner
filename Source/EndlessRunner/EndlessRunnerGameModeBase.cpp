// Copyright 2019 Ashley Hipgrave. All rights reserved.

#include "EndlessRunnerGameModeBase.h"
#include "RunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EndlessRunnerFloor.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

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

	if (FMath::RandRange(0, 3) == 0)
	{
		NextSpawnLocation.X += 350.f;
	}
	else if (FMath::RandRange(0, 3) == 1)
	{
		FloorTile->SpawnObstacle();
	}
}

void AEndlessRunnerGameModeBase::NotifyPlayerObstacleCollision()
{
	ARunnerCharacter* PlayerCharacter = Cast<ARunnerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (PlayerCharacter)
	{
		PlayerCharacter->NotifyObstacleCollision();
	}
}
