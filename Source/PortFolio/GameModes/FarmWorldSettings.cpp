// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmWorldSettings.h"

AFarmWorldSettings::AFarmWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AActor* AFarmWorldSettings::GetLevelMovePoints(int32 num) const
{
	if (LevelMovePoints.IsEmpty())
	{
		//‹ó‚È‚çnullptr‚ğ•Ô‚·
		return nullptr;
	}
	else if (LevelMovePoints[num])
	{
		//num‚Ì”z—ñ”Ô†‚ª‚ ‚é‚È‚ç‚»‚ê‚ğ•Ô‚·
		return LevelMovePoints[num];
	}
	else
	{
		//‹ó‚Å‚Í‚È‚¢‚¯‚Çnum‚ª‚È‚¢‚È‚ç0”Ô–Ú‚Ì”z—ñ‚ğ•Ô‚·
		UE_LOG(LogTemp, Warning, TEXT("GetLevelMovePoint: return LevelMovePoints[0];"));
		return LevelMovePoints[0];

	}
	
}

