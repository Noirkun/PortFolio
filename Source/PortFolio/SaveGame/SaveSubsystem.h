// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tasks/Task.h"
#include "SaveSubsystem.generated.h"

using namespace UE::Tasks;
/**
 * 
 */
UCLASS()
class PORTFOLIO_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	static USaveSubsystem* Get();
public:
	
	 FSaveParmeterStruct GameParameter;

	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void SaveGame(bool& clearSave);

	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void LoadGame(bool& clearLoad);
	
};
