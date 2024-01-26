// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tasks/Task.h"
#include "PortFolio/Widget/Fade/FadeScreenSubsystem.h"
#include "../LevelManager/LevelSubsystemManager.h"
#include "SaveSubsystem.generated.h"

using namespace UE::Tasks;

//セーブスロットは一つだけ使う予定なので定数でスロット名と番号を指定
#define SAVE_SLOT_NAME "SaveSlotName"
#define SAVE_SLOT_NUM 0

/**
 * 　セーブとロードを管理するサブシステムクラス
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
	 @param MoveLevelPointNum GetAttatchに渡す引数
	*/
	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void LoadGame(bool& clearLoad,bool IsStart=false,const int32 MoveLevelPointNum=0);
	
	 /* セーブしたスロットを削除する用の関数
	  @param ReturnResetSlot スロットを削除できたかどうか
	 */
	UFUNCTION(BlueprintCallable,Category="Save/Load")
	void ResetSaveSlot(bool& ReturnResetSlot);

	// スタートセーブスロットがあるかを返す関数
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Save/Load")
	bool DoesStartSaveSlot();
	

	UPROPERTY( EditAnywhere, Category = "LoadingWidget Settings")
	TSubclassOf<UUserWidget> LoadingWidget;


	// セーブスロットをロードする関数
	void LoadSaveSlot(FString SlotName, int32 SlotNum);

	// セーブスロットを作成する関数
	bool CreateSaveSlot(FString SlotName, int32 SlotNum);
	
private:
	// セーブスロットがあるかどうかを返す関数
	bool CheckSaveSlot(bool IsStart=false);


	

};