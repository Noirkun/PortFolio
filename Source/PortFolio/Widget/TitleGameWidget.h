// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Widget/BaseGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TitleGameWidget.generated.h"

/**
 * 　タイトル画面のUIを作るクラス
 */
UCLASS()
class PORTFOLIO_API UTitleGameWidget : public UBaseGameWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	UTextBlock* TitleText;

	UPROPERTY()
	UButton* StartButton;

	UPROPERTY()
	UButton* ContinueButton;

	UPROPERTY()
	UButton* SettingButton;

	UPROPERTY()
	UButton* QuitButton;

	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnContinueButtonClicked();
	UFUNCTION()
	void OnSettingButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();

	virtual void BindFunctions() override;
};
