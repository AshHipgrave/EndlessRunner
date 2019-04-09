// Copyright 2019 Ashley Hipgrave. All rights reserved.

#include "EndlessRunnerFloor.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

AEndlessRunnerFloor::AEndlessRunnerFloor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"));
	FloorMesh->SetupAttachment(SceneComponent);

	FloorMesh->SetWorldScale3D(FVector(1.f, 3.f, 1.f));
	FloorMesh->SetRelativeScale3D(FVector(1.f, 3.f, 1.f));

	AttachComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachComponent"));
	AttachComponent->SetupAttachment(SceneComponent);
}