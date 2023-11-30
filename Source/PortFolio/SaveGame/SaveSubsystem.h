// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../LevelManager/LevelSubsystemManager.h"
#include "Tasks/Task.h"
#include "SaveSubsystem.generated.h"

using namespace UE::Tasks;

//セーブスロットは一つだけ使う予定なので定数でスロット名と番号を指定
#define SAVE_SLOT_NAME "SaveSlotName"
#define SAVE_SLOT_NUM 0

/**
 * 　セーブとロードを管理するクラス
 */
UCLASS()
class PORTFOLIO_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:


	//inline static ULevelSubsystemManager LevelManager;
	
	inline static USaveSubsystem* instance;
	
	static USaveSubsystem* Get();
	
	
	/* ゲームをセーブする用の関数
	 @param clearSave セーブができたかどうか
	 @param IsEnd ゲームを終了するときに呼ぶかどうか
	*/
	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void SaveGame(bool& clearSave,bool IsEnd=false);

	/* ゲームをロードする用の関数(Slotになにもないと動作されない)
	 @param clearLoad ロードができたかどうか
	 @param IsStart ゲームを開始するときに呼ぶかどうか
	*/
	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void LoadGame(bool& clearLoad,bool IsStart=false);
	
	 /* セーブしたスロットを削除する用の関数
	  @param ReturnResetSlot スロットを削除できたかどうか
	 */
	UFUNCTION(BlueprintCallable,Category="Save/Load")
	void ResetSaveSlot(bool& ReturnResetSlot);

	
};