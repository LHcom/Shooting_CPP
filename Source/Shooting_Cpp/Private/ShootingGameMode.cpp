// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "MainWidget.h"
#include "ShootingSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShootingGameMode::BeginPlay ( )
{
	Super::BeginPlay ( );

	LoadGameData();

	if (MainWidget)
	{
		MainUI = CreateWidget<UMainWidget> ( GetWorld ( ) , MainWidget );

		if (MainUI)
		{
			MainUI->AddToViewport ( );
			MainUI->SetHighScore(HighScore);
		}
	}
}

void AShootingGameMode::AddScore ( int32 point )
{
	CurrentScore += point;
	/*GEngine->AddOnScreenDebugMessage ( 1 , 10 , FColor::Red ,
		FString::Printf ( TEXT ( "현재 점수 : %d" ) , CurrentScore ) );*/

	// 현재 점수 출력
	PrintScore();
	if (CurrentScore > HighScore)
	{
		HighScore = CurrentScore;
		SaveGameData();
		PrintHighScore();
	}
}

void AShootingGameMode::PrintScore ( )
{
	// MainUI 가 있다면
	if (MainUI)
	{
		// TxtScore 텍스트 블록에 현재 점수 값으로 입력한다.
		MainUI->SetScore(CurrentScore);
	}
}

void AShootingGameMode::PrintHighScore()
{
	if (MainUI)
		MainUI->SetHighScore( HighScore );
}

void AShootingGameMode::SaveGameData()
{
	// ShootingSaveGame 객체 생성
	UShootingSaveGame* sg = Cast<UShootingSaveGame>
			(UGameplayStatics::CreateSaveGameObject( UShootingSaveGame::StaticClass()));
	// ShootingSaveGame 객체의 HighScoreSave 값을 갱신
	sg->HighScoreSave = HighScore;
	// 파일로 저장
	UGameplayStatics::SaveGameToSlot(sg, SaveSlotName , UserIndex );
}

void AShootingGameMode::LoadGameData()
{
	// 파일이 존재하는지 확인
	bool isExist = UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex);

	// 파일이 없으면 중단
	if (!isExist) return;

	// 파일이 있으면 읽어서 ShootingSaveGame 객체를 생성
	UShootingSaveGame* sg = Cast< UShootingSaveGame>
				(UGameplayStatics::LoadGameFromSlot( SaveSlotName , UserIndex ));

	if (!sg) return;

	// ShootingSaveGame 객체에세 HighScoreSave값을 읽어서 HighScore로 갱신
	HighScore = sg->HighScoreSave;
}

void AShootingGameMode::SetHP(float curHP, float maxHP)
{
	if (!MainUI) return;
	MainUI->SetHP(curHP, maxHP);
}

void AShootingGameMode::ShowGameOver(bool bShow)
{
	if (!MainUI) return;

	// 게임을 bShow 값에 따라 일시정지 상태로 만든다.
	UGameplayStatics::SetGamePaused(GetWorld(), bShow);
	// 플레이어 컨트롤러를 가져와서
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		// 마우스 커서를 bShow 값에 따라 숨기거나 보여준다.
		pc->SetShowMouseCursor(bShow);
		// Input Mode를 bShow 값에 따라 GameOnly 또는 UIOnly로 설정한다.
		if (bShow)
			pc->SetInputMode(FInputModeUIOnly());
		else
			pc->SetInputMode(FInputModeGameOnly());
	}

	MainUI->ShowGameOver(bShow);
}
