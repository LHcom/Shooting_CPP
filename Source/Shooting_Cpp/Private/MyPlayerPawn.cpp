// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerPawn.h"

#include "BulletActor.h"
#include "ShootingGameMode.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

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

	// MeshComp의 콜리전 비활성화
	MeshComp->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

	// MeshCompo의 Transform 설정
	//// 1
	//MeshComp->SetRelativeLocation ( FVector ( -130 , 0 , 20 ) );
	//MeshComp->SetRelativeRotation ( FRotator ( 0 , 90 , -90 ) );
	//MeshComp->SetRelativeScale3D ( FVector ( 0.1 ) );

	//// 2
	//MeshComp->SetRelativeTransform ( FTransform ( FQuat ( FRotator ( 0 , 90 , -90 ) ) ,
	//					FVector ( -130 , 0 , 20 ) ,
	//						FVector ( 0.1 ) ) );

	// 3
	MeshComp->SetRelativeLocationAndRotation ( FVector ( -130 , 0 , 20 ) , FRotator ( 0 , 90 , -90 ) );
	MeshComp->SetRelativeScale3D ( FVector ( 0.1 ) );

	// 오버랩 이벤트 활성화
	BoxComp->SetGenerateOverlapEvents ( true );
	// 충돌 응답을 Query and Physics로 설정
	BoxComp->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	// Object Type을 Player로 설정
	BoxComp->SetCollisionObjectType ( ECC_GameTraceChannel1 );

	// 모든 채널을 Ignore로 설정
	BoxComp->SetCollisionResponseToAllChannels ( ECollisionResponse::ECR_Ignore );
	// Enemy 충돌을 Overlap으로 설정
	BoxComp->SetCollisionResponseToChannel ( ECC_GameTraceChannel3 , ECollisionResponse::ECR_Overlap );
}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay ( )
{
	Super::BeginPlay ( );

	HP = MaxHP;

	GM = Cast<AShootingGameMode> ( GetWorld ( )->GetAuthGameMode ( ) );
	if (GM)
	{
		GM->SetHP ( HP , MaxHP );
		GM->ShowGameOver ( false );
	}

	//// 게임을 진행 상태로 만든다.
	//UGameplayStatics::SetGamePaused ( GetWorld ( ) , false );
	//APlayerController* pc = GetWorld()->GetFirstPlayerController();
	//if (pc)
	//{
	//	pc->SetShowMouseCursor ( false ); // 마우스 커서를 숨긴다.
	//	pc->SetInputMode(FInputModeGameOnly()); // Input Mode 설정
	//}

	for (int32 i = 0;i < MaxBulletCount;++i)
	{
		// 스폰할 객체의 대한 스폰 옵션을 설정하는 구조체
		FActorSpawnParameters params;
		// 스폰 과정에 충돌이 발생해도 스폰을 강제로 진행한다.
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ABulletActor* bullet = GetWorld ( )->SpawnActor<ABulletActor> ( BulletFactory , params );
		bullet->SetActive ( false );
		Magazine.Add ( bullet );
	}
}

// Called every frame
void AMyPlayerPawn::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	// 사용자의 입력에 따라 상하좌우로 이동하고 싶다.
	// P = P0 + v(방향 * 속도)t

	// 방향
	FVector dir = FVector ( 0 , h , v );
	// dir의 길이를 1로 만들고 싶다.
	dir.Normalize ( );
	// 등속 운동
	FVector p0 = GetActorLocation ( );
	FVector velocity = dir * Speed;
	FVector p = p0 + velocity * DeltaTime;
	SetActorLocation ( p );

	if (AutoFire)
	{
		CurrentTime += DeltaTime;

		if (CurrentTime >= FireTime)
		{
			SetBulletTransform();
			CurrentTime = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent ( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent ( PlayerInputComponent );

	// BindAxis (연결할 이벤트 이름, 연결할 함수가 있는 클래스, 연결할 함수의 주소값)
	PlayerInputComponent->BindAxis ( TEXT ( "Horizontal" ) , this , &AMyPlayerPawn::OnAxisHorizontal );
	PlayerInputComponent->BindAxis ( TEXT ( "Vertical" ) , this , &AMyPlayerPawn::OnAxisVertical );

	// Fire함수 바인딩
	//PlayerInputComponent->BindAction ( TEXT ( "Fire" ) , IE_Pressed , this , &AMyPlayerPawn::OnActionFire );
	PlayerInputComponent->BindAction ( TEXT ( "Fire" ) , IE_Pressed , this , &AMyPlayerPawn::OnActionAutoFire_Hold );
	PlayerInputComponent->BindAction ( TEXT ( "Fire" ) , IE_Released , this , &AMyPlayerPawn::OnActionAutoFire_Hold );

	PlayerInputComponent->BindAction ( TEXT ( "AutoFire_1" ) , IE_Pressed , this , &AMyPlayerPawn::OnActionAutoFire );
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

void AMyPlayerPawn::OnActionFire ( )
{
	SetBulletTransform ( );
}

void AMyPlayerPawn::SetDamage ( int32 damage )
{
	HP -= damage;
	if (GM)
	{
		// HpBar 갱신
		GM->SetHP ( HP , MaxHP );
	}
}

void AMyPlayerPawn::SetBulletTransform ( )
{
	// ArrowComponent의 Transform 값을 가져온다.
	FTransform FirePos = ArrowComp->GetComponentTransform ( );

	for (int32 i = 0;i < Magazine.Num ( );++i)
	{
		if (!Magazine[i]->MeshComp->GetVisibleFlag ( ))
		{
			FirePos.SetScale3D ( Magazine[i]->MeshComp->GetComponentScale ( ) );

			// 총알을 활성화하고 총구 위치에 이동시킨다.
			Magazine[i]->SetActive ( true );
			Magazine[i]->SetActorTransform ( FirePos );

			// 총알 발사 사운드 재생
			UGameplayStatics::SpawnSound2D ( GetWorld ( ) , FireSound );

			break;
		}
	}
}

void AMyPlayerPawn::OnActionAutoFire ( )
{
	AutoFire = !AutoFire;
	CurrentTime = 0.0f;
}

void AMyPlayerPawn::OnActionAutoFire_Hold()
{
	AutoFire = !AutoFire;

	if (AutoFire)
		CurrentTime = FireTime;
}

