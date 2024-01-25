// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Struct/SaveParmeterStruct.h"
#include "SaveSystem.generated.h"

/**
 * 　セーブ用の構造体を持つセーブゲーム
 */
UCLASS()
class PORTFOLIO_API USaveSystem : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FSaveParmeterStruct SaveParameter;
};
