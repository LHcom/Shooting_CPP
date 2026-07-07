// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "MyPlayerPawn.h"
#include "ShootingGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor::AEnemyActor ( )
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 컴포넌트를 추가해서 Root 컴포넌트로 설정
	BoxComp = CreateDefaultSubobject<UBoxComponent> ( TEXT ( "BoxComp" ) );
	// BoxComp를 Root 컴포넌트로 설정
	SetRootComponent ( BoxComp );
	// Box Extent 설정
	BoxComp->SetBoxExtent ( FVector ( 50 , 50 , 50 ) );

	// 메시 컴포넌트를 추가해서 Root 컴포넌트에 Attach
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "MeshComp" ) );
	// Root 컴포넌트에 Attach
	MeshComp->SetupAttachment ( BoxComp );

	// 생성자 도우미를 이용해서 에셋을 로드하고 싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh ( TEXT ( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	// 에셋 로드가 성공했으면?
	if (tempMesh.Succeeded ( ))
		MeshComp->SetStaticMesh ( tempMesh.Object );

	// MeshComp 충돌 비활성화
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	// Collision Preset을 Enemy 프리셋으로 설정
	BoxComp->SetCollisionProfileName ( FName ( "Enemy" ) );

	BoxComp->OnComponentBeginOverlap.AddDynamic ( this , &AEnemyActor::OnEnemyOverlap );
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay ( )
{
	Super::BeginPlay ( );

	// 기본으로 이동할 방향을 앞 방향으로 세팅
	Dir = GetActorForwardVector ( );

	// 1부터 100 사이의 정수 랜덤 값을 만든다
	int32 rndNum = FMath::RandRange ( 1 , 100 );

	// 만약, 랜덤 값이 RandomRate 이하라면 플레이어 방향으로 Dir을 세팅
	if (rndNum <= RandomRate)
	{
		// 현재 플레이어
		if (APawn* Target = GetWorld ( )->GetFirstPlayerController ( )->GetPawn ( ))
		{
			if (IsValid ( Target ))
			{
				Dir = ( Target->GetActorLocation ( ) - this->GetActorLocation ( ) ).GetSafeNormal ( );
			}
		}
	}
}

// Called every frame
void AEnemyActor::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	// p = p0 + vt
	FVector p = GetActorLocation ( ) + Dir * Speed * DeltaTime;
	SetActorLocation ( p );
}

void AEnemyActor::OnEnemyOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if (AMyPlayerPawn* player = Cast<AMyPlayerPawn> ( OtherActor ))
	{
		// 플레이어 체력을 1 감소시킨다.
		player->SetDamage ( 1 );

		// 플레이어가 사망했다면
		if (player->HP <= 0)
		{
			// 플레이어를 제거한다.
			player->Destroy ( );

			// 현재 게임모드를 가져온다.
			AShootingGameMode* currentGameMode = Cast<AShootingGameMode> ( GetWorld ( )->GetAuthGameMode ( ) );
			if (currentGameMode)
			{
				//// 게임을 일시 정지 상태로 만든다.
				//UGameplayStatics::SetGamePaused ( GetWorld ( ) , true );
				//APlayerController* pc = GetWorld ( )->GetFirstPlayerController ( );
				//if (pc)
				//{
				//	pc->SetShowMouseCursor ( true ); // 마우스 커서를 보여준다.
				//	pc->SetInputMode(FInputModeUIOnly()); // Input Mode 설정
				//}

				// GameOverWidget을 보여준다.
				currentGameMode->ShowGameOver ( true );
			}
		}

		Destroy ( );
	}
}
