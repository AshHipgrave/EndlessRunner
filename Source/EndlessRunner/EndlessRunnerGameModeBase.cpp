// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunnerGameModeBase.h"
#include "RunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_RunnerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
