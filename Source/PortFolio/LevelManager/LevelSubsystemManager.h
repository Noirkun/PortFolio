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
	virtual void LevelLoadCompleted();

	UFUNCTION()
	virtual void UnLevelLoadCompleted();  

public:

	// レベルをロードする関数
	void LoadLevel(const FName& level);
	// レベルをアンロードする関数
	void UnloadLevel(const FName& level);
	// レベルを表示する関数
	bool ShowLevel(const FName& level) const;
	// レベルを非表示にする関数
	bool HideLevel(const FName& level) const;
	// レベルのロードが完了したかどうかを返す関数
	bool IsCompleted() const;


	
private:
	bool Complete;
	FName LoadLevelName;
	FLatentActionInfo LoadLatentAction;
	FLatentActionInfo UnloadLatentAction;

};
