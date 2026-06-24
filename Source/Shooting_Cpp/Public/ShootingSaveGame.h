// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShootingSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_CPP_API UShootingSaveGame : public ULocalPlayerSaveGame
{
	GENERATED_BODY()
	
public:
	// 저장하고 싶은 변수
	UPROPERTY(BlueprintReadWrite, Category="Default|SaveGame")
	int32 HighScoreSave;
};
