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

	//Levelをロードした時に呼び出される関数
	UFUNCTION()
	virtual void LevelLoadCompleted();

	//Levelをアンロードした時に呼び出される関数
	UFUNCTION()
	virtual void UnLevelLoadCompleted();  

public:
	
	/* レベルをロードする関数
	@param clearSave セーブができたかどうか
	*/
	void LoadLevel(const FName& level);
	
	/* レベルを表示する関数
	@param clearSave セーブができたかどうか
	*/
	bool ShowLevel(const FName& level) const;
	// レベルを非表示にする関数
	bool HideLevel(const FName& level) const;
	// レベルのロードが完了したかどうかを返す関数
	bool IsCompleted() const;

	
	UUserWidget* LoadingWidget;
	
private:
	bool Complete;
	FName LoadLevelName;
	FLatentActionInfo LoadLatentAction;
	FLatentActionInfo UnloadLatentAction;

};
