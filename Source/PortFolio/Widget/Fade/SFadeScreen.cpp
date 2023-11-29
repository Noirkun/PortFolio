// Fill out your copyright notice in the Description page of Project Settings.


#include "SFadeScreen.h"

void SFadeScreen::Construct(const FArguments& InArgs)
{
	FadeParams = InArgs._FadeParams;
	OnFadeFinished = InArgs._OnFadeFinished;
}

void SFadeScreen::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	
	TimeRemaining = FMath::Max(TimeRemaining - InDeltaTime, 0.0f);
	//時間が0になったら終了する
	if (TimeRemaining == 0.0f)
	{
		FinishFade();
		return;
	}

	//Fadeの色を計算する
	const FLinearColor NextColor = FadeParams.ToColor - (FadeParams.ToColor - FadeParams.FromColor) * TimeRemaining / FadeParams.Time;
	ApplyFade(NextColor);
}

void SFadeScreen::StartFade()
{
	SetImage(FCoreStyle::Get().GetBrush("WhiteBrush"));

	if(FadeParams.Time <= 0.0f)
	{
		FinishFade();
		return;
	}

	//Fadeの時間を設定する
	TimeRemaining = FadeParams.Time;
	//Fadeの最初の色を設定する
	ApplyFade(FadeParams.FromColor);

	SetCanTick(true);
	
}

void SFadeScreen::FinishFade()
{
	ApplyFade(FadeParams.ToColor);
	
	OnFadeFinished.ExecuteIfBound();
	FadeParams.OnFinishFadeDelegate.ExecuteIfBound();
	SetCanTick(false);
}

void SFadeScreen::ApplyFade(const FLinearColor& NextColor)
{
	SetColorAndOpacity(NextColor);
}

