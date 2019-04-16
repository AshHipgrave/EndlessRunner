// Copyright 2019 Ashley Hipgrave. All rights reserved.

#include "EndlessRunnerFloor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "FloorObstacleComponent.h"
#include "EndlessRunnerGameModeBase.h"

AEndlessRunnerFloor::AEndlessRunnerFloor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"));
	FloorMesh->SetupAttachment(SceneComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorMeshObject(TEXT("StaticMesh'/Game/Meshes/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (FloorMeshObject.Succeeded())
	{
		FloorMesh->SetStaticMesh(FloorMeshObject.Object);
		FloorMesh->SetWorldScale3D(FVector(3.f, 1.f, 1.f));
		FloorMesh->SetRelativeScale3D(FVector(3.f, 1.f, 1.f));
	}

	AttachComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachComponent"));
	AttachComponent->SetupAttachment(SceneComponent);
	AttachComponent->SetRelativeLocation(FVector(300.f, 0.f, 0.f));

	EdgeCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("EdgeCollisionComponent"));
	EdgeCollisionComponent->SetupAttachment(SceneComponent);
	EdgeCollisionComponent->SetRelativeLocation(FVector(150.f, 0.f, 490.f));
	EdgeCollisionComponent->SetRelativeScale3D(FVector(1.75f, 2.f, 13.f));
	EdgeCollisionComponent->SetWorldScale3D(FVector(1.75f, 2.f, 13.f));
	EdgeCollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 32.f));

	EdgeCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EdgeCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	EdgeCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	EdgeCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndlessRunnerFloor::HandleEdgeBeginOverlap);

	ObstacleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorObstacleMesh"));
	ObstacleMeshComponent->SetupAttachment(SceneComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObstacleMeshObject(TEXT("StaticMesh'/Game/Meshes/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (ObstacleMeshObject.Succeeded())
	{
		ObstacleMeshComponent->SetStaticMesh(ObstacleMeshObject.Object);
		ObstacleMeshComponent->SetWorldScale3D(FVector(0.25f, 1.0f, 0.25f));
		ObstacleMeshComponent->SetRelativeScale3D(FVector(0.25f, 1.0f, 0.25f));
		ObstacleMeshComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 100.0f));

		ObstacleMeshComponent->SetVisibility(false);
		ObstacleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ObstacleMeshComponent->CanCharacterStepUpOn = ECB_No;
	}

	ObstacleCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollisionComponent"));
	ObstacleCollisionComponent->SetupAttachment(ObstacleMeshComponent);

	ObstacleCollisionComponent->SetRelativeScale3D(FVector(1.05f, 1.0f, 1.0f));
	ObstacleCollisionComponent->SetWorldScale3D(FVector(1.05f, 1.05f, 1.05f));
	
	ObstacleCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ObstacleCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ObstacleCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ObstacleCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndlessRunnerFloor::HandleObstacleComponentBeginOverlap);
}

void AEndlessRunnerFloor::SpawnObstacle()
{
	ObstacleMeshComponent->SetVisibility(true);
	ObstacleMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ObstacleCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AEndlessRunnerFloor::HandleEdgeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->CreateFloorTile();
		SetLifeSpan(2);
	}
}

void AEndlessRunnerFloor::HandleObstacleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->NotifyPlayerObstacleCollision();
	}
}

FVector AEndlessRunnerFloor::GetAttachLocation() const
{
	return AttachComponent->GetComponentLocation();
}
