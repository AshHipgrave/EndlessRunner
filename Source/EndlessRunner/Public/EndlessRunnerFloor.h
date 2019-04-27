// Copyright 2019 Ashley Hipgrave. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerFloor.generated.h"

class UBoxComponent;
class UArrowComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerFloor : public AActor
{
	GENERATED_BODY()
	
public:
	AEndlessRunnerFloor();

protected:

	UFUNCTION()
	void HandleEdgeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleObstacleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	/** Root component for attaching floor components together */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	/** Floor mesh the player will run along */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMesh;

	/** Point to join a floor components together at */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachComponent;

	/** Collider for the edge of the floor, triggers the spawning of additional floor components to keep the level persisting */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* EdgeCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ObstacleMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ObstacleCollisionComponent;

public:
	UFUNCTION()
	void SpawnObstacle();

	FVector GetAttachLocation() const;
};
