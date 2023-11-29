// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelSubsystemManager.generated.h"

/**
 *  レベルのロードな管理するクラス
 */
UCLASS()
class PORTFOLIO_API ULevelSubsystemManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//Levelをロードした時に呼び出される関数
	UFUNCTION()
	virtual void LevelLoadCompleted();

	//Levelをアンロードした時に呼び出される関数
	UFUNCTION()
	virtual void UnLevelLoadCompleted();  

public:
	
	/* レベルをロードする関数
	@param Level ロードするレベルの名前
	*/
	void LoadLevel(const FName& level);
	
	// レベルのロードが完了したかどうかを返す関数
	bool IsCompleted() const;

	
	UUserWidget* LoadingWidget;
	
private:
	bool Complete;
	FName LoadLevelName;
	FLatentActionInfo LoadLatentAction;
	FLatentActionInfo UnloadLatentAction;

};
