// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"

#include "SaveSystem.h"
#include "UObject/UObjectGlobals.h"



USaveSubsystem* USaveSubsystem::Get()
{
	if(instance==nullptr)
	{
		instance=NewObject<USaveSubsystem>();
		check(instance)
		instance->AddToRoot();
	}
		return instance;
}

//セーブする際に呼ぶ関数
void USaveSubsystem::SaveGame(bool& clearSave,bool IsEnd)
{
	if(IsEnd)
	{
		clearSave = CreateSaveSlot(SAVE_SLOT_NAME,SAVE_SLOT_NUM);
	}
	else
	{
		clearSave = CreateSaveSlot(SAVE_SLOT_NOW_GAME_NAME,SAVE_SLOT_NOW_GAME_NUM);
	}
}

//ロードする際に呼ぶ関数
void USaveSubsystem::LoadGame(bool& clearLoad, bool IsStart, const int32 MoveLevelPointNum)
{
	clearLoad = false;
	
	//セーブスロットが作られているか確認
	if(!CheckSaveSlot(IsStart))
	{
		UE_LOG(LogTemp, Log, TEXT("Not SaveSlot"));
		clearLoad = false;
		return;
	}
	
	//ゲーム開始時に呼ぶかどうか
	if (IsStart)
	{
		LoadSaveSlot(SAVE_SLOT_NAME,SAVE_SLOT_NUM);
		clearLoad = true;
	}
	//ゲーム中に呼ぶ
	else
	{
		LoadSaveSlot(SAVE_SLOT_NOW_GAME_NAME,SAVE_SLOT_NOW_GAME_NUM);
		clearLoad = true;
	}
}

void USaveSubsystem::ResetSaveSlot(bool& ReturnResetSlot)
{
	//ゲームスロットが作られているか確認
	if(UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME,SAVE_SLOT_NUM))
	{
		//作られていた場合削除する。
		UGameplayStatics::DeleteGameInSlot(SAVE_SLOT_NAME,SAVE_SLOT_NUM);
		UE_LOG(LogTemp, Log, TEXT("ResetSaveSlot"));
		ReturnResetSlot=true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not SaveSlot"));
		ReturnResetSlot=false;
	}
}

bool USaveSubsystem::DoesStartSaveSlot()
{
	//ゲームスロットが作られているか確認
	if(UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME,SAVE_SLOT_NUM))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool USaveSubsystem::CheckSaveSlot(bool IsStart)
{
	if(IsStart)
	{
		//セーブ用スロットが作られているか確認
		if (!UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME,SAVE_SLOT_NUM))
		{
			//セーブ用ゲームスロットが作られていない場合
			UE_LOG(LogTemp, Log, TEXT("Not SaveSlot"));
			return false;
		}
	}
	else
	{
		//一時セーブ用ゲームスロットが作られているか確認
		if (!UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NOW_GAME_NAME,SAVE_SLOT_NOW_GAME_NUM))
		{
			//一時セーブ用ゲームスロットが作られていない場合
			UE_LOG(LogTemp, Log, TEXT("Not NowGameSaveSlot"));
			return false;
		}
	}
	return true;
}

bool USaveSubsystem::CreateSaveSlot(FString SlotName, int32 SlotNum)
{
	//プレイヤーを取得
	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0);
	APortFolioCharacter* MyCharacter=Cast<APortFolioCharacter,ACharacter>(Character);

	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance=Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	//セーブする値のセット
	SaveGameInstance->SaveParameter={GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
	   MyCharacter->dataNum,MyCharacter->GetTransform()};

	UE_LOG(LogTemp, Log, TEXT("StartSaveGame"));
	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, SlotNum);

}

void USaveSubsystem::LoadSaveSlot(FString SlotName, int32 SlotNum)
{
	UGameInstance* _GameInst = GetWorld() -> GetGameInstance();

	//LevelManagerから非同期ロード用の関数を呼ぶ
	auto LevelManager = _GameInst -> GetSubsystem<ULevelSubsystemManager>();
	auto FadeSubsystem = _GameInst -> GetSubsystem<UFadeScreenSubsystem>();

	UE_LOG(LogTemp, Log, TEXT("Start"));
	// セーブ用スロットを取得
	USaveSystem* SaveGameInstance = Cast<USaveSystem>(
		UGameplayStatics::LoadGameFromSlot(SlotName, SlotNum));
	if (!SaveGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not SaveSlot Instance"));
		return;
	}
	// LevelNameの場所に移動する
	const FString& LevelName = SaveGameInstance -> SaveParameter . level;

	// フェードアウトが終わったらレベルを移動する処理をバインドしておく
	FFadeScreenDelegate FadeDelegate;
	FadeDelegate . BindLambda([LevelManager,LevelName]()
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
		LevelManager -> LoadLevel(*LevelName);
	});
	// フェードアウトを行う
	FadeSubsystem -> AddFadeOutScreen(1.0f, FLinearColor::Black, FadeDelegate);

	//LoadMapの最後にデータを入れるようにする。
	FCoreUObjectDelegates::PostLoadMapWithWorld . AddLambda(
		[SlotName,SlotNum,FadeSubsystem, LevelManager](UWorld* World)
		{
			// プレイヤーのパラメータをアタッチする
			LevelManager -> AttachPlayerStatus(World, SlotName, SlotNum, true);
			// フェードインを行う
			FadeSubsystem -> AddFadeInScreen();
			UE_LOG(LogTemp, Warning, TEXT("FadeOutClear"));
		});
}
