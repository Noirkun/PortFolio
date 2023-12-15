// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"
#include "PortFolio/Widget/Fade/FadeScreenSubsystem.h"
#include "../LevelManager/LevelSubsystemManager.h"
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
	
	//プレイヤーを取得
	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0);
	APortFolioCharacter* MyCharacter=Cast<APortFolioCharacter,ACharacter>(Character);

	if(IsEnd)
	{
		// USaveSystemクラスを取得
		USaveSystem* SaveGameInstance=Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
		//セーブする値のセット
		SaveGameInstance->SaveParameter={GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
		   MyCharacter->dataNum,MyCharacter->GetTransform()};

		UE_LOG(LogTemp, Log, TEXT("StartSaveGame"));
		clearSave = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NAME, SAVE_SLOT_NUM);
	}
	else
	{
		// USaveSystemクラスを取得
		USaveSystem* SaveGameInstance=Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
		//セーブする値のセット
		SaveGameInstance->SaveParameter={GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
		   MyCharacter->dataNum,MyCharacter->GetTransform()};

		UE_LOG(LogTemp, Log, TEXT("NowSaveGame"));
		clearSave = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);
	}
}

//ロードする際に呼ぶ関数
void USaveSubsystem::LoadGame(bool& clearLoad, bool IsStart, const int32 MoveLevelPointNum)
{
	clearLoad = false;
	if(IsStart)
	{
		//セーブ用スロットが作られているか確認
		if (!UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME,SAVE_SLOT_NUM))
		{
			//セーブ用ゲームスロットが作られていない場合
			UE_LOG(LogTemp, Log, TEXT("Not SaveSlot"));
			clearLoad = false;
			return;
		}
	}
	else
	{
		//一時セーブ用ゲームスロットが作られているか確認
		if (!UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NOW_GAME_NAME,SAVE_SLOT_NOW_GAME_NUM))
		{
			//一時セーブ用ゲームスロットが作られていない場合
			UE_LOG(LogTemp, Log, TEXT("Not NowGameSaveSlot"));
			clearLoad = false;
			return;
		}
	}
	
	UGameInstance* _GameInst = GetWorld() -> GetGameInstance();

	//LevelManagerから非同期ロード用の関数を呼ぶ
	auto LevelManager = _GameInst -> GetSubsystem<ULevelSubsystemManager>();
	auto FadeSubsystem = _GameInst -> GetSubsystem<UFadeScreenSubsystem>();

	//ゲーム開始時に呼ぶかどうか
	if (IsStart)
	{
		UE_LOG(LogTemp, Log, TEXT("Start"));
		// セーブ用スロットを取得
		 USaveSystem* SaveGameInstance = Cast<USaveSystem>(
			UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, SAVE_SLOT_NUM));
		if(SaveGameInstance)
		{
			const FString& LevelName = SaveGameInstance -> SaveParameter . level;
			LevelManager -> LoadLevel(*LevelName);
			

			FFadeScreenDelegate FadeDelegate;
			FadeDelegate.BindLambda([LevelManager,LevelName]()
			{
					UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
					LevelManager->LoadLevel(*LevelName);
			});
			FadeSubsystem->AddFadeOutScreen(1.0f, FLinearColor::Black, FadeDelegate);

			//LoadMapの最後にデータを入れるようにする。
			FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([FadeSubsystem, LevelManager](UWorld* World)
				{
					LevelManager->AttachPlayerStatus(World, SAVE_SLOT_NAME, SAVE_SLOT_NUM,true);

					FadeSubsystem->AddFadeInScreen();
					UE_LOG(LogTemp, Warning, TEXT("FadeOutClear"));
				});

			clearLoad = true;

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Not StartSaveSlot Instance"));
			clearLoad = false;

		}
	}
	//ゲーム中に呼ぶ
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not Start"));
		// 一時セーブ用スロットを取得
		 USaveSystem* SaveGameInstance = Cast<USaveSystem>(
			UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM));

		UE_LOG( LogTemp, Warning, TEXT("LevelName=%s"), *SaveGameInstance -> SaveParameter.playerTransform.ToString());
		
		if(SaveGameInstance)
		{
			const FString& LevelName = SaveGameInstance -> SaveParameter . level;

			// LevelNameが現在のレベルと同じでない場合のみロードする
			if (GetWorld() -> GetOuter() -> GetPathName() != LevelName)
			{
				// スロットに保存されているレベル以外をロードするときの処理があれば書く
			}
			

			FFadeScreenDelegate FadeDelegate;

			// フェードアウトが終わったらレベルを移動する処理をバインドしておく
			FadeDelegate.BindLambda([LevelManager,LevelName]()
			{
				UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
				LevelManager -> LoadLevel(*LevelName);
			});
			// フェードアウトを行う
			FadeSubsystem -> AddFadeOutScreen(1.0f, FLinearColor::Black, FadeDelegate);

			//LoadMapの最後にデータを入れるようにする。
			FCoreUObjectDelegates::PostLoadMapWithWorld . AddLambda([this,FadeSubsystem,LevelManager,MoveLevelPointNum](UWorld* World)
			{
				LevelManager->AttachPlayerStatus(World, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM,false,MoveLevelPointNum);
				// フェードインを行う
				FadeSubsystem -> AddFadeInScreen();
				UE_LOG(LogTemp, Warning, TEXT("Fade LoadClear"));
			});
				clearLoad = true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Not NowGameSaveSlot Instance"));
			clearLoad = false;

		}
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