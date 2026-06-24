// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

class UMainWidget;

/**
 * 
 */
UCLASS()
class SHOOTING_CPP_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	int32 CurrentScore = 0; // 현재 점수
	int32 HighScore = 0; // 최고 점수

	// 현재 뷰포트에 로드된 위젯 저장용 변수
	UPROPERTY()
	UMainWidget* MainUI;

public:
	void AddScore(int32 point);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidget;

	void PrintScore();
	void PrintHighScore();

	// SlotName, UserIndex
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveSlotName = TEXT("HighScore");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UserIndex = 0;

	void SaveGameData();
	void LoadGameData();
};
