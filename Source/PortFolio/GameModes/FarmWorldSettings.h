// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "FarmWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AFarmWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

	AFarmWorldSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, Category = "LoadingWidget Settings")
	TSubclassOf<UUserWidget> LoadingWidget;

public:
	TSubclassOf<UUserWidget> GetLoadingWidget() const { return LoadingWidget; }

};
