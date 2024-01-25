// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "FarmWorldSettings.generated.h"

/**
 * 　Loading用にWorldSettingsの拡張
 */
UCLASS()
class PORTFOLIO_API AFarmWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

	AFarmWorldSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, Category = "LoadingWidget Settings")
	TSubclassOf<UUserWidget> LoadingWidget;

	UPROPERTY(EditAnywhere, Category = "LevelMovePoint")
		TArray<AActor*> LevelMovePoints;

public:
	TSubclassOf<UUserWidget> GetLoadingWidget() const { return LoadingWidget; }

	AActor* GetLevelMovePoints(int32 num = 0) const;

};
