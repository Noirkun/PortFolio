// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tasks/Task.h"
#include "SaveSubsystem.generated.h"

using namespace UE::Tasks;

//セーブスロットは一つだけ使う予定なので定数でスロット名と番号を指定
#define SAVE_SLOT_NAME "SaveSlotName"
#define SAVE_SLOT_NUM 0


UCLASS()
class PORTFOLIO_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	inline static USaveSubsystem* instance;
	
	static USaveSubsystem* Get();
	
public:
	
	 FSaveParmeterStruct GameParameter;

	UFUNCTION(BlueprintCallable, Category = "Save/Load",meta = (ToolTip = "ゲームをセーブする用の関数"))
	void SaveGame(bool& clearSave);

	UFUNCTION(BlueprintCallable, Category = "Save/Load",meta = (ToolTip = "ゲームをロードする用の関数(Slotになにもないと動作されない)"))
	void LoadGame(bool& clearLoad);
	
	UFUNCTION(BlueprintCallable,Category="Save/Load",meta = (ToolTip = "セーブしたスロットを削除する用の関数"))
	void ResetSaveSlot();
	
};