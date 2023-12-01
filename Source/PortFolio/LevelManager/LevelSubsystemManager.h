// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PortFolio/GameManager/GameManager.h"
#include "LevelSubsystemManager.generated.h"

#define SAVE_SLOT_NOW_GAME_NAME "SaveNowSlotName"
#define SAVE_SLOT_NOW_GAME_NUM 1

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


	//非同期でレベルをロードする関数(LevelFuncLibraryに移動済み)
	/*
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
		void AsyncOpenLevel(ELevelNamesType Level);
	*/

	
	/* プレイヤーのパラメータをアタッチする用の関数
	@param World 
	@param SlotName
	@param SlotNum
	*/
	void AttachPlayerStatus(UWorld* World, const FString& SlotName, const int32 SlotNum);
	

	/* レベルをロードする関数
	@param Level ロードするレベルの名前
	*/
	void LoadLevel(const FName& level);
	
	// レベルのロードが完了したかどうかを返す関数
	bool IsCompleted() const;

	UPROPERTY()
	UUserWidget* LoadingScreenWidget=nullptr;
private:
	bool Complete;
	FName LoadLevelName;
	FLatentActionInfo LoadLatentAction;
	FLatentActionInfo UnloadLatentAction;

};
