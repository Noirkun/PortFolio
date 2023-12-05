// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

virtual void Init() override;
	
};
