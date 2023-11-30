// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSubsystemManager.h"
#include "Async/Async.h"
#include "Containers/Ticker.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include <PortFolio/PortFolioCharacter.h>
#include <PortFolio/SaveGame/SaveSystem.h>
#include "PortFolio/Widget/Fade/Struct/FadeScreenStruct.h"
#include <PortFolio/Widget/Fade/FadeScreenSubsystem.h>

void ULevelSubsystemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadLatentAction.CallbackTarget = this;
	LoadLatentAction.ExecutionFunction = "LevelLoadCompleted";
	LoadLatentAction.UUID = 1;
	LoadLatentAction.Linkage = 0;

	UnloadLatentAction.CallbackTarget = this;
	UnloadLatentAction.ExecutionFunction = "LevelLoadCompleted";
	UnloadLatentAction.UUID = 1;
	UnloadLatentAction.Linkage = 0;
	
}

void ULevelSubsystemManager::LevelLoadCompleted()
{
	//完了したらLevelを移動する。
	UGameplayStatics::OpenLevel( this, LoadLevelName );
	Complete = true;
	
}

void ULevelSubsystemManager::UnLevelLoadCompleted()
{
	UGameplayStatics::LoadStreamLevel( this, LoadLevelName, false, false, LoadLatentAction );
}

void ULevelSubsystemManager::AsyncOpenLevel(const TSoftObjectPtr<UWorld> Level)
{
	const FName LevelFName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));
	if (Level == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NotLevel Data"));
		return;
	}

	FString LevelName = LevelFName.ToString();
	//UE_LOG(LogTemp, Warning, TEXT("Async MoveLevel=%s"),*LevelName);

	//プレイヤーを取得
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	//セーブする値のセット
	SaveGameInstance->SaveParameter = { GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
	   MyCharacter->dataNum,MyCharacter->GetTransform() };

	UE_LOG(LogTemp, Log, TEXT("NowSaveGame"));
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);


	if (SaveGameInstance)
	{


		// LevelNameが現在のレベルと同じでない場合のみロードする
		if (GetWorld()->GetOuter()->GetPathName() != LevelName)
		{
			// スロットに保存されているレベル以外をロードするときの処理があれば書く
		}

		UGameInstance* _GameInst = GetWorld()->GetGameInstance();





		auto FadeSubsystem = _GameInst->GetSubsystem<UFadeScreenSubsystem>();
		FFadeScreenDelegate FadeDelegate;

		// フェードアウトが終わったらレベルを移動する処理をバインドしておく
		FadeDelegate.BindLambda([this, LevelName]()
			{
				UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
				LoadLevel(*LevelName);
			});
		// フェードアウトを行う
		FadeSubsystem->AddFadeOutScreen(1.0f, FLinearColor::Black, FadeDelegate);

		//LoadMapの最後にデータを入れるようにする。
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([this, FadeSubsystem](UWorld* World)
			{
				AttachPlayerStatus(World, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);
				// フェードインを行う
				FadeSubsystem->AddFadeInScreen();
				UE_LOG(LogTemp, Warning, TEXT("Fade LoadClear"));
			});
	}

}

void ULevelSubsystemManager::AttachPlayerStatus(UWorld* World, const FString& SlotName, const int32 SlotNum)
{
	const USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot(SlotName, SlotNum));
	const FString& LevelName = SaveGameInstance->SaveParameter.level;

	// PostLoadMapWithWorldのデリゲートを削除
	FCoreUObjectDelegates::PostLoadMapWithWorld.Clear();
	if (World)
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);

		if (Character)
		{
			APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

			// プレイヤーに値を割り振る
			MyCharacter->playerStatus = SaveGameInstance->SaveParameter.playerStatus;
			MyCharacter->EXP = SaveGameInstance->SaveParameter.playerEXP;
			MyCharacter->dataNum = SaveGameInstance->SaveParameter.levelData;
			MyCharacter->SetActorTransform(SaveGameInstance->SaveParameter.playerTransform);

			UE_LOG(LogTemp, Warning, TEXT("AttachPlayerStatus"));

		}
	}

}

void ULevelSubsystemManager::LoadLevel(const FName& level)
{
	Complete = false;
	UGameplayStatics::UnloadStreamLevel( this, GetWorld()->GetFName(), LoadLatentAction, false );
	LoadLevelName=level;
	
}

bool ULevelSubsystemManager::IsCompleted() const
{
	return Complete;
}

