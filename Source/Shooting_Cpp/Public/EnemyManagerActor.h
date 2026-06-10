// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

class UArrowComponent;
class AEnemyActor;

UCLASS()
class SHOOTING_CPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Default|Comp")
	USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, Category = "Default|Comp")
	UArrowComponent* SpawnArrow;

	// 현재 시간, 생성 시간, EnemyFactory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime = 0.0f;
	UPROPERTY ( EditAnywhere , BlueprintReadWrite )
	float MakeTime = 1.0f;
	UPROPERTY ( EditAnywhere , BlueprintReadWrite )
	TSubclassOf<AEnemyActor> EnemyFactory;

	void MakeEnemy();

	UPROPERTY()
	FTimerHandle Hnd;
};
