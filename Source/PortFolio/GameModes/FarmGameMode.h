// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmGameMode.generated.h"

/**
 *  ゲームモード
 */
UCLASS()
class PORTFOLIO_API AFarmGameMode : public AGameModeBase
{
	GENERATED_BODY()


	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
};
