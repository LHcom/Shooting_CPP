// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTING_CPP_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UBoxComponent* BoxComp;
	// 메시 컴포넌트를 추가해서 Root 컴포넌트에 Attach
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UStaticMeshComponent* MeshComp;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Move" )
	float Speed = 800.0f; // 플레이어 이동 속도
};
