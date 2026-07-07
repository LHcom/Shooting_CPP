// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTING_CPP_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button_Restart;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* Button_Quit;

	UFUNCTION()
	void Restart();
	UFUNCTION()
	void Quit();
};
