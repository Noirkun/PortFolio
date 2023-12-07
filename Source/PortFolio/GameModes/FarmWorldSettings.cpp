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
		//空ならnullptrを返す
		return nullptr;
	}
	else if (LevelMovePoints[num])
	{
		//numの配列番号があるならそれを返す
		return LevelMovePoints[num];
	}
	else
	{
		//空ではないけどnumがないなら0番目の配列を返す
		UE_LOG(LogTemp, Warning, TEXT("GetLevelMovePoint: return LevelMovePoints[0];"));
		return LevelMovePoints[0];

	}
	
}

