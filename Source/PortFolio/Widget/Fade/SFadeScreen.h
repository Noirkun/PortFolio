// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Images/SImage.h"
#include "PortFolio/Widget/Fade/Struct/FadeScreenStruct.h"

/**
 * 　Fadeを行うためのSImage
 */
class PORTFOLIO_API SFadeScreen : public SImage
{
public:
	SLATE_BEGIN_ARGS(SFadeScreen)
	{}
	SLATE_ARGUMENT(FFadeScreenParams, FadeParams)
	SLATE_EVENT(FFadeScreenDelegate, OnFadeFinished)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//Fadeを開始する
	void StartFade();
	
private:
	//Fadeを終了する
	void FinishFade();
	//Fadeを適用する
	void ApplyFade(const FLinearColor& NextColor);
	
	FFadeScreenParams FadeParams;
	FFadeScreenDelegate OnFadeFinished;

	//Fadeまでの時間
	double TimeRemaining = 0;
};
