// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"

USaveSubsystem* USaveSubsystem::Get()
{
	 USaveSubsystem* instance = nullptr;

	if (GEngine != nullptr)
	{
		FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		instance = Cast<USaveSubsystem>(context->OwningGameInstance);
	}
	return instance;
}

//セーブする際に呼ぶ関数
void USaveSubsystem::SaveGame(bool& clearSave)
{
	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance=Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));

	//プレイヤーを取得
	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0);
	APortFolioCharacter* MyCharacter=Cast<APortFolioCharacter,ACharacter>(Character);

	//セーブする値のセット
	 SaveGameInstance->SaveParameter	={GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
		MyCharacter->dataNum,MyCharacter->GetTransform()};
	GameParameter= SaveGameInstance->SaveParameter;
	UE_LOG(LogTemp, Log, TEXT("セーブ"));
	 clearSave = UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveSlotName", 0);
}

//ロードする際に呼ぶ関数
void USaveSubsystem::LoadGame(bool& clearLoad)
{
	// USaveSystemクラスを取得
	const USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot("SaveSlotName", 0));
	const FString& LevelName = SaveGameInstance -> SaveParameter.level;
	// スロットがあるか確認
	if (SaveGameInstance)
	{
		//プレイヤーの取得
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this -> GetWorld(), 0);
		APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

		//タスクを使って順番に行う
		FTask TaskOpenLevel = Launch(TEXT("OpenLevel"), [this,LevelName]
		                             {
			                             // レベルをロードして格納（同期処理なので非同期も検討）
			                             if (GetWorld() -> GetOuter() -> GetPathName() != LevelName)
			                             {
				                             // マップを推移する処理
				                             UGameplayStatics::OpenLevel(this, *LevelName);
			                             }
			                             //FPlatformProcess::Sleep(1.0f);
			                             UE_LOG(LogTemp, Log, TEXT("TaskA End"));
		                             }
		);
		
		// TaskOpenLevelが完了するまでは起動しない
		FTask TaskB = Launch(TEXT("Task Prereqs TaskB"), [this,MyCharacter,SaveGameInstance]
		                     {
			                     // プレイヤーに値を割り振る
			                     MyCharacter->playerStatus = SaveGameInstance->SaveParameter.playerStatus;
			                     MyCharacter->EXP = SaveGameInstance->SaveParameter.playerEXP;
			                     MyCharacter->dataNum = SaveGameInstance->SaveParameter.levelData;
			                     MyCharacter->SetActorTransform(SaveGameInstance->SaveParameter.playerTransform);
			                     UE_LOG(LogTemp, Warning, TEXT("LoadClear"));
			                     FPlatformProcess::Sleep(0.2f);
			                     UE_LOG(LogTemp, Log, TEXT("TaskB End"));
		                     }, TaskOpenLevel
		);
TaskB.Wait();
		clearLoad = true;
	}
	clearLoad = false;
}
