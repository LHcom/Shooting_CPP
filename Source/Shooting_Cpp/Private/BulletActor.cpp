// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "ShootingGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABulletActor::ABulletActor ( )
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

	// (X=0.750000,Y=0.250000,Z=1.000000)
	BoxComp->SetRelativeScale3D ( FVector ( 0.75f , 0.25f , 1.0f ) );

	// MeshComp 충돌 비활성화
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	// Collision Preset을 Bullet 프리셋으로 설정
	BoxComp->SetCollisionProfileName ( FName ( "Bullet" ) );

	BoxComp->OnComponentBeginOverlap.AddDynamic ( this , &ABulletActor::OnBulletOverlap );
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay ( )
{
	Super::BeginPlay ( );

}

// Called every frame
void ABulletActor::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	// p = p0 + vt
	FVector p0 = GetActorLocation ( );
	FVector velocity = GetActorForwardVector ( ) * Speed; // GetActorForwardVector = 앞 방향 X축 (Speed, 0, 0) xyz
	FVector p = p0 + velocity * DeltaTime;
	SetActorLocation ( p );
}

void ABulletActor::OnBulletOverlap ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	// 충돌한 액터를 AEnemyActor 클래스로 변환한다.
	AEnemyActor* enemy = Cast<AEnemyActor> ( OtherActor );

	// 캐스팅이 성공해서 enemy 에 값이 있다면
	if (enemy != nullptr)
	{
		// 게임모드를 가져온다
		AGameModeBase* currentMode = GetWorld ( )->GetAuthGameMode ( );
		// 가져온 게임모드를 AShootingGameMode로 변환
		AShootingGameMode* shootingGameMode = Cast<AShootingGameMode> ( currentMode );
		if (shootingGameMode)
			shootingGameMode->AddScore ( 1 );

		// 충돌한 액터를 제거한다.
		enemy->Destroy ( );

		// 사운드 재생
		UGameplayStatics::SpawnSound2D ( GetWorld ( ) , EnemyDestroySound );

		// 이펙트 재생
		UGameplayStatics::SpawnEmitterAtLocation ( GetWorld ( ) , EnemyDestroyEffect , enemy->GetActorLocation ( ) );

		// 자기 자신도 제거한다.
		//Destroy ( );

		SetActive ( false );
	}
}

void ABulletActor::SetActive ( bool isActive )
{
	MeshComp->SetVisibility ( isActive );

	if (isActive)
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	else
		BoxComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
}

