// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"

//#include "EnemyActor.h"
#include "../Public/EnemyActor.h"

#include "Components/ArrowComponent.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor ( )
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent> ( TEXT ( "RootScene" ) );
	SetRootComponent ( RootScene );

	SpawnArrow = CreateDefaultSubobject<UArrowComponent> ( TEXT ( "SpawnArrow" ) );
	SpawnArrow->SetupAttachment ( RootScene );
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay ( )
{
	Super::BeginPlay ( );

	GetWorld()->GetTimerManager().SetTimer( Hnd , this, &AEnemyManagerActor::MakeEnemy , MakeTime, true);
}

void AEnemyManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(Hnd);

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AEnemyManagerActor::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	//// 시간이 흐름
	//CurrentTime += DeltaTime; // CurrentTime = CurrentTime + DeltaTime;
	//// 만약, 현재 누적 시간이 생성 시간을 넘으면
	//if (CurrentTime >= MakeTime)
	//{
	//	MakeEnemy ( );

	//	CurrentTime = 0.0f; // 누적 시간을 초기화한다.
	//}
}

void AEnemyManagerActor::MakeEnemy()
{
	// Enemy를 스폰한다.
	AEnemyActor* Enemy = GetWorld ( )->SpawnActor<AEnemyActor> ( EnemyFactory , SpawnArrow->GetComponentTransform ( ) );
}

