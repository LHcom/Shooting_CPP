// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadZone.h"

#include "Components/BoxComponent.h"

// Sets default values
ADeadZone::ADeadZone()
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
	// Collision Preset을 DeadZone 프리셋으로 설정
	BoxComp->SetCollisionProfileName ( FName ( "DeadZone" ) );

	BoxComp->OnComponentBeginOverlap.AddDynamic ( this , &ADeadZone::OnDeadZoneOverlap );
}

// Called when the game starts or when spawned
void ADeadZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeadZone::OnDeadZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

