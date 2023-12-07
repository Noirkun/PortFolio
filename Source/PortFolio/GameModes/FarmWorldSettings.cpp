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
		//��Ȃ�nullptr��Ԃ�
		return nullptr;
	}
	else if (LevelMovePoints[num])
	{
		//num�̔z��ԍ�������Ȃ炻���Ԃ�
		return LevelMovePoints[num];
	}
	else
	{
		//��ł͂Ȃ�����num���Ȃ��Ȃ�0�Ԗڂ̔z���Ԃ�
		UE_LOG(LogTemp, Warning, TEXT("GetLevelMovePoint: return LevelMovePoints[0];"));
		return LevelMovePoints[0];

	}
	
}

