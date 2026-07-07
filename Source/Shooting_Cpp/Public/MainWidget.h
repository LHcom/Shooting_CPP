// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UGameOverWidget;
class UProgressBar;
class UTextBlock;

/**
 *
 */
UCLASS ( )
class SHOOTING_CPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY ( )

protected:
	virtual void NativeConstruct ( ) override;

public:
	UPROPERTY ( EditAnywhere , meta = ( BindWidget ) )
	UTextBlock* TxtScore;

	UPROPERTY ( EditAnywhere , meta = ( BindWidget ) )
	UTextBlock* TxtHighScore;

	void SetScore ( int32 NewScore );
	void SetHighScore ( int32 NewScore );

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* HpBar;

	void SetHP(float curHp, float maxHp);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGameOverWidget* GameOverWidget;

	void ShowGameOver(bool bShow);
};
