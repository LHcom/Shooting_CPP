// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerPawn.h"

#include "BulletActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyPlayerPawn::AMyPlayerPawn ( )
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	// Arrow 컴포넌트 추가
	ArrowComp = CreateDefaultSubobject<UArrowComponent> ( TEXT ( "ArrowComp" ) );
	// Root 컴포넌트에 Attach
	ArrowComp->SetupAttachment ( BoxComp );
	ArrowComp->SetRelativeLocationAndRotation ( FVector ( 0 , 0 , 100 ) , FRotator ( 90 , 0 , 0 ) );
}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay ( )
{
	Super::BeginPlay ( );

}

// Called every frame
void AMyPlayerPawn::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	// 사용자의 입력에 따라 상하좌우로 이동하고 싶다.
	// P = P0 + v(방향 * 속도)t

	// 방향
	FVector dir = FVector(0, h, v);
	// dir의 길이를 1로 만들고 싶다.
	dir.Normalize();
	// 등속 운동
	FVector p0 = GetActorLocation ( );
	FVector velocity = dir * Speed;
	FVector p = p0 + velocity * DeltaTime;
	SetActorLocation(p);
}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent ( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent ( PlayerInputComponent );

	// BindAxis (연결할 이벤트 이름, 연결할 함수가 있는 클래스, 연결할 함수의 주소값)
	PlayerInputComponent->BindAxis ( TEXT ( "Horizontal" ) , this , &AMyPlayerPawn::OnAxisHorizontal );
	PlayerInputComponent->BindAxis ( TEXT ( "Vertical" ) , this , &AMyPlayerPawn::OnAxisVertical );

	// Fire함수 바인딩
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayerPawn::OnActionFire );
}

void AMyPlayerPawn::OnAxisHorizontal ( float value )
{
	h = value;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("H = %.2f"), h));
}

void AMyPlayerPawn::OnAxisVertical ( float value )
{
	v = value;
	//GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "V = %.2f" ) , v ) );
}

void AMyPlayerPawn::OnActionFire()
{
	// 마우스를 클릭하면 총알을 생성하고 싶다.

	// ArrowComponent의 Transform 값을 가져온다.
	FTransform FirePos = ArrowComp->GetComponentTransform ( );

	// FirePos 정보로 ABulletActor를 생성한다.
	GetWorld()->SpawnActor<ABulletActor>( BulletFactory , FirePos );
}

