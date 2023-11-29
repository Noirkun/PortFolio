// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FadeScreenStruct.generated.h"



DECLARE_DELEGATE(FFadeScreenDelegate);
/**
 *  Fadeに必要な項目の構造体
 */
USTRUCT(BlueprintType)
struct PORTFOLIO_API FFadeScreenParams
{
 GENERATED_USTRUCT_BODY()

 //Fadeが終わった時に呼ばれるデリゲート
  FFadeScreenDelegate OnFinishFadeDelegate;
 
 //Fadeまでの時間
 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeScreenStruct")
 double Time;

 //Fadeする前の色
 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeScreenStruct")
 FLinearColor FromColor;
 
 //Fadeしていく色
 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeScreenStruct")
 FLinearColor ToColor;

 FFadeScreenParams():Time(0.0f), FromColor(FLinearColor::Black), ToColor(FLinearColor::Black)
 {
 }

 FFadeScreenParams(const double InTime, const FLinearColor& InFromColor, const FLinearColor& InToColor, const FFadeScreenDelegate& InOnFinishFadeDelegate)
 :OnFinishFadeDelegate(InOnFinishFadeDelegate), Time(InTime), FromColor(InFromColor), ToColor(InToColor)
 {
 }
 
};
