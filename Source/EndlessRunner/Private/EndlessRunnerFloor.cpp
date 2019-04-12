// Copyright 2019 Ashley Hipgrave. All rights reserved.

#include "EndlessRunnerFloor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

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
	EdgeCollisionComponent->SetRelativeLocation(FVector(140.f, 0.f, 300.f));
	EdgeCollisionComponent->SetRelativeScale3D(FVector(1.25f, 2.f, 1.f));
	EdgeCollisionComponent->SetWorldScale3D(FVector(1.25f, 2.f, 7.f));
	EdgeCollisionComponent->SetBoxExtent(FVector(32.f, 32.f, 32.f));

	EdgeCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EdgeCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	EdgeCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	EdgeCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndlessRunnerFloor::HandleEdgeBeginOverlap);
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

FVector AEndlessRunnerFloor::GetAttachLocation() const
{
	return AttachComponent->GetComponentLocation();
}
