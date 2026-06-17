// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_CPP_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	int32 CurrentScore = 0; // 현재 점수

public:
	void AddScore(int32 point);
};
