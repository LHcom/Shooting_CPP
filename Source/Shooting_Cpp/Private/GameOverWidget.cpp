// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct ( )
{
	Super::NativeConstruct ( );

	// 각 버튼 입력 이벤트에 대응하는 함수를 연결한다.
	Button_Restart->OnClicked.AddDynamic ( this , &UGameOverWidget::Restart );
	Button_Quit->OnClicked.AddDynamic ( this , &UGameOverWidget::Quit );
}

void UGameOverWidget::Restart ( )
{
	// 현재 레벨의 이름을 가져와서
	FString mapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	// 레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), FName(*mapName));
}

void UGameOverWidget::Quit ( )
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
									EQuitPreference::Quit, false);
}
