// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "Components/BoxComponent.h"

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
	if (tempMesh.Succeeded())
		MeshComp->SetStaticMesh(tempMesh.Object);

	// (X=0.750000,Y=0.250000,Z=1.000000)
	BoxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));
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

}

