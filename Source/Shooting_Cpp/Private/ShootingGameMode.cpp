// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

void AShootingGameMode::AddScore ( int32 point )
{
	CurrentScore += point;
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, 
						FString::Printf(TEXT("현재 점수 : %d"), CurrentScore));
}
