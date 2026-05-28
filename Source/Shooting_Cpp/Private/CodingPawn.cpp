// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingPawn.h"

// Sets default values
ACodingPawn::ACodingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACodingPawn::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%d"), Number);
	UE_LOG(LogTemp, Warning, TEXT("%.2f"), Distance);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bGood); // 0, 1
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);

	// 배열
	TArray<int32> Arr;
	Arr.Empty(10);
	Arr.Add(10);
	Arr.Add(11);
	Arr.Add(12);

	if (!Arr.Contains(5))
	{
		Arr.Add(5);
	}

	UE_LOG(LogTemp, Warning, TEXT("요소의 개수 = %d개"), Arr.Num());
	UE_LOG(LogTemp, Warning, TEXT("메모리 개수 = %d개"), Arr.GetSlack());

	//for (int32 i = 0; i < Arr.Num(); ++i)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%d"), Arr[i]);
	//}

	for (int32 item : Arr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), item);
	}

	// TMap<key, value>

	TMap<FString, int32> map;

	map.Add("Coin", 10);
	if (!map.Contains("Coin"))
		map.Add("Coin", 20);
	else
		map["Coin"] = 30;

	UE_LOG(LogTemp, Warning, TEXT("%d"), map["Coin"]);

	for (TPair<FString, int32> pair : map)
		UE_LOG(LogTemp, Warning, TEXT("%s, %d"), *pair.Key, pair.Value);
}

// Called every frame
void ACodingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACodingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 ACodingPawn::MyAddCallable(int32 a, int32 b)
{
	return a + b;
}

int32 ACodingPawn::MyAddPure(int32 a, int32 b)
{
	return a + b;
}

int32 ACodingPawn::MyAddNativeEvent_Implementation(int32 a, int32 b)
{
	return a + b;
}
