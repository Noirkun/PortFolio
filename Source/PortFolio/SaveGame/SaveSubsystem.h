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
	USaveSystem* GetSaveSystem(const FString& SlotName, const int32& SlotIndex);
	UFUNCTION(BlueprintCallable, DisplayName = "Save", Category = "GameSave")
	void Save(const FString& SlotName, const int32& SlotIndex);
	UFUNCTION(BlueprintCallable, DisplayName = "Load", Category = "GameSave")
	void Load(const FString& SlotName, const int32& SlotIndex);
};
