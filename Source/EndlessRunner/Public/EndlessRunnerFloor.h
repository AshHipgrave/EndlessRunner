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
	// Sets default values for this actor's properties
	AEndlessRunnerFloor();

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

public:
	FTransform GetAttachTransform() const;
};
