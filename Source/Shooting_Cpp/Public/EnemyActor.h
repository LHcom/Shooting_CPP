// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTING_CPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 충돌체 컴포넌트를 추가해서 Root 컴포넌트로 설정
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UBoxComponent* BoxComp;
	// 메시 컴포넌트를 추가해서 Root 컴포넌트에 Attach
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UStaticMeshComponent* MeshComp;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Move" )
	float Speed = 600.0f;
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Move" )
	FVector Dir;
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Move" )
	int32 RandomRate = 30;
};
