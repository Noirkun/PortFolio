// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelSubsystemManager.generated.h"

UCLASS()
class PORTFOLIO_API ULevelSubsystemManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	

	
	UFUNCTION()
	void Completed();      // <- これが完了時に呼び出される関数です。上にUFUNCTION()の設定が必ず要ります。

public:
	void LoadLevel(const FName& level);
	void UnloadLevel(const FName& level);
	bool ShowLevel(const FName& level) const;
	bool HideLevel(const FName& level) const;
	bool IsCompleted() const;
	
private:
	FLatentActionInfo LatentAction;
	bool Complete;
};
