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



public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "LoadingScreen",meta = (AssetBundles = "Explicit"))
	TSoftClassPtr<UUserWidget> LoadingScreenClass;

	
};
