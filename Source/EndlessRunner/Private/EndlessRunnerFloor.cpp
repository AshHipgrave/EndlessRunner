// Copyright 2019 Ashley Hipgrave. All rights reserved.

#include "EndlessRunnerFloor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AEndlessRunnerFloor::AEndlessRunnerFloor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"));
	FloorMesh->SetupAttachment(SceneComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorMeshObject(TEXT("StaticMesh'/Game/MobileStarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (FloorMeshObject.Succeeded())
	{
		FloorMesh->SetStaticMesh(FloorMeshObject.Object);
		FloorMesh->SetWorldScale3D(FVector(3.f, 1.f, 1.f));
		FloorMesh->SetRelativeScale3D(FVector(3.f, 1.f, 1.f));
	}

	AttachComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachComponent"));
	AttachComponent->SetupAttachment(SceneComponent);
	AttachComponent->SetRelativeLocation(FVector(150.f, 0.f, 0.f));

	EdgeCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("EdgeCollisionComponent"));
	EdgeCollisionComponent->SetupAttachment(SceneComponent);
	EdgeCollisionComponent->SetRelativeLocation(FVector(150.f, 0.f, 60.f));
	EdgeCollisionComponent->SetRelativeScale3D(FVector(0.5f, 2.f, 1.f));
	EdgeCollisionComponent->SetWorldScale3D(FVector(0.f, 2.f, 1.f));
	EdgeCollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 32.f));
}

FTransform AEndlessRunnerFloor::GetAttachTransform() const
{
	return AttachComponent->GetRelativeTransform();
}
