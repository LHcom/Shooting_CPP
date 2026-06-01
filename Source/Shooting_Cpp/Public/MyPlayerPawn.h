// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerPawn.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS ( )
class SHOOTING_CPP_API AMyPlayerPawn : public APawn
{
	GENERATED_BODY ( )

public:
	// Sets default values for this pawn's properties
	AMyPlayerPawn ( );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay ( ) override;

public:
	// Called every frame
	virtual void Tick ( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent ( class UInputComponent* PlayerInputComponent ) override;

public:
	// 충돌체 컴포넌트를 추가해서 Root 컴포넌트로 설정
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UBoxComponent* BoxComp;
	// 메시 컴포넌트를 추가해서 Root 컴포넌트에 Attach
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UStaticMeshComponent* MeshComp;
	// 총알을 발사할 방향 (총구)
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Comp" )
	UArrowComponent* ArrowComp;

	// 사용자의 입력에 따라 상하좌우로 이동하고 싶다.
	// 좌우 값을 저장할 변수
	float h;
	// 상하 값을 저장할 변수
	float v;

	// 입력을 받아올 함수
	void OnAxisHorizontal ( float value );
	void OnAxisVertical ( float value );

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Default|Move" )
	float Speed = 500.0f; // 플레이어 이동 속도
};
