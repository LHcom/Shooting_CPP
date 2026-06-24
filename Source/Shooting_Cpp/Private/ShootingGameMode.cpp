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
