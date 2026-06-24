// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetScore(0);
	SetHighScore(0);
}

void UMainWidget::SetScore(int32 NewScore)
{
	TxtScore->SetText ( FText::AsNumber ( NewScore ) );
	/*FText txtScore = FText::Format(FText::FromString(TEXT("현재 점수 : {0}")), FText::AsNumber ( NewScore ));
	TxtScore->SetText ( txtScore );*/
}

void UMainWidget::SetHighScore(int32 NewScore)
{
	//TxtHighScore->SetText ( FText::AsNumber ( NewScore ) );
	TxtHighScore->SetText ( FText::AsNumber ( NewScore ) );
}

void UMainWidget::SetHP(float curHp, float maxHp)
{
	if (!HpBar) return;
	HpBar->SetPercent(curHp / maxHp);
}
