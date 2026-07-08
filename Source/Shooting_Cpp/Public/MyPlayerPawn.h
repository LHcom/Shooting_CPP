// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerPawn.generated.h"

class AShootingGameMode;
class ABulletActor;
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

	// 총알을 발사할 때 사용할 함수
	UFUNCTION()
	void OnActionFire();

	// 총알 클래스 원형을 저장할 변수
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABulletActor> BulletFactory; // UClass

	// 최대 체력 / 현재 체력
	float HP;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite )
	float MaxHP = 2.0f;

	void SetDamage(int32 damage);

	UPROPERTY()
	AShootingGameMode* GM;

	UPROPERTY(EditAnywhere, Category = "Default|Sound")
	USoundBase* FireSound;

	// 총알을 오브젝트 풀 처리하고 싶다.
	// [필요 요소]
	// 최초 생성할 총알 개수
	UPROPERTY(EditAnywhere, Category = "Default|Pool")
	int32 MaxBulletCount = 20;

	// 총알 목록
	UPROPERTY(EditAnywhere, Category = "Default|Pool")
	TArray<ABulletActor*> Magazine; 

	void SetBulletTransform();

	bool AutoFire = false;
	float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Default|Fire")
	float FireTime = 0.2f;

	UFUNCTION()
	void OnActionAutoFire();

	UFUNCTION()
	void OnActionAutoFire_Hold();
};
