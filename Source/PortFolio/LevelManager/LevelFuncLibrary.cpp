// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFuncLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"
#include "PortFolio/LevelManager/LevelSubsystemManager.h"
#include "PortFolio/SaveGame/SaveSystem.h"
#include "PortFolio/SaveGame/SaveSubsystem.h"
#include "PortFolio/Widget/Fade/FadeScreenSubsystem.h"

void ULevelFuncLibrary::AsyncOpenLevel(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level,
                                       double FadeTime, const int32 MoveLevelPointNum)
{
	// ロードしている場合は何もしない
	if (bLoading)
	{
		return;
	}
	bLoading = true;
	// ワールドを取得
	UWorld* World = GEngine -> GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level . ToString()));
	//	Level名を確認
	UE_LOG(LogTemp, Warning, TEXT("LevelName=%s"), *LevelName.ToString());

	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance = Cast<USaveSystem>(
		UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));

	// SaveSubsystemを取得
	USaveSubsystem* SaveSubsystem = World -> GetGameInstance() -> GetSubsystem<USaveSubsystem>();

	//Level上にプレイヤーがいる場合のみセーブする
	SavePlayerStatus(World, SaveGameInstance);
	
	// SaveGameInstanceが有効ならロードする
	if (!SaveGameInstance)
	{
		return;
	}
	// LevelNameが現在のレベルと同じでない場合のみロードする
	if (World -> GetOuter() -> GetPathName() != LevelName . ToString())
	{
		// スロットに保存されているレベル以外をロードするときの処理があれば書く
	}

	//Instanceを取得してサブシステムを呼び出す
	UGameInstance* _GameInst = World -> GetGameInstance();
	auto LevelManager = _GameInst -> GetSubsystem<ULevelSubsystemManager>();
	auto FadeSubsystem = _GameInst -> GetSubsystem<UFadeScreenSubsystem>();

	FFadeScreenDelegate FadeDelegate;

	// フェードアウトし、レベルを移動する
	ChangeMapWithFading(LevelManager, FadeSubsystem, LevelName, FadeDelegate, FadeTime, MoveLevelPointNum);
	
}

void ULevelFuncLibrary::SavePlayerStatus(UWorld* World, USaveSystem* SaveGameInstance)
{
	if (UGameplayStatics::GetPlayerCharacter(World, 0))
	{
		//プレイヤーを取得
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
		APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);
		
		//セーブする値のセット
		SaveGameInstance->SaveParameter =
		{
			World->GetOuter()->GetPathName(),
			MyCharacter->playerStatus,
			MyCharacter->EXP,
			MyCharacter->dataNum,
			MyCharacter->GetTransform()
			};

		UE_LOG(LogTemp, Log, TEXT("NowSaveGame"));
		// 現在のプレイヤーのデータをセーブする
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Player"));
		return;
	}
}

void ULevelFuncLibrary::ChangeMapWithFading(ULevelSubsystemManager* LevelManager, UFadeScreenSubsystem* FadeSubsystem,
	const FName& LevelName, FFadeScreenDelegate& FadeDelegate,double FadeTime,const int32 MoveLevelPointNum)
{
	// フェードアウトが終わったらレベルを移動する処理をバインドしておく
	FadeDelegate.BindLambda([LevelManager, LevelName]()
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
			LevelManager->LoadLevel(*LevelName.ToString());
		});
	// フェードアウトを行う
	FadeSubsystem->AddFadeOutScreen(FadeTime, FLinearColor::Black, FadeDelegate);

	//LoadMapの最後にデータを入れるようにする。
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([LevelManager, FadeSubsystem,FadeTime,MoveLevelPointNum](UWorld* World)
		{
			LevelManager->AttachPlayerStatus(World, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM,false,MoveLevelPointNum);
			// フェードインを行う
			FadeSubsystem->AddFadeInScreen(FadeTime);
			bLoading = false;
			UE_LOG(LogTemp, Warning, TEXT("LevelFunc: Fade LoadClear"));
		});
}
