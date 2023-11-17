// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"


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
	UE_LOG(LogTemp, Log, TEXT("SaveGame"));
	 clearSave = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NAME, SAVE_SLOT_NUM);
}

//ロードする際に呼ぶ関数
void USaveSubsystem::LoadGame(bool& clearLoad)
{
	clearLoad = false;
	//ゲームスロットが作られているか確認
	if(!UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME,SAVE_SLOT_NUM))
	{
		UE_LOG(LogTemp, Log, TEXT("Not SaveSlot"));
		clearLoad = false;
		return;
	}
	
	// USaveSystemクラスを取得
	const USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, SAVE_SLOT_NUM));
	const FString& LevelName = SaveGameInstance -> SaveParameter.level;
	// スロットがあるか確認
	if (SaveGameInstance)
	{
		//プレイヤーの取得
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this -> GetWorld(), 0);
		APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

		//タスクを使って順番に行う
		FTask TaskOpenLevel = Launch(TEXT("Task OpenLevel"), [this,LevelName]
		                             {
			                             // レベルをロードして格納（同期処理なので非同期も検討）
			                             if (GetWorld() -> GetOuter() -> GetPathName() != LevelName)
			                             {

			                             	UGameInstance* _GameInst = GetWorld()->GetGameInstance();
auto LevelManager = _GameInst->GetSubsystem<ULevelSubsystemManager>();
			                             	LevelManager->LoadLevel(*LevelName);
			                             	
				                             // マップを推移する処理(LevelManagerなどを作るのが良いかもしれない)
			                             	  //UGameplayStatics::OpenLevel(this, *LevelName);
			                             }
			                             //FPlatformProcess::Sleep(1.0f);
			                             UE_LOG(LogTemp, Log, TEXT("TaskOpenLevel End"));
		                             }
		);
		
		// TaskOpenLevelが完了するまでは起動しない
		FTask TaskPlayerState = Launch(TEXT("Task TaskPlayerState"), [this,MyCharacter,SaveGameInstance]
		                     {
			                     // プレイヤーに値を割り振る
			                     MyCharacter->playerStatus = SaveGameInstance->SaveParameter.playerStatus;
			                     MyCharacter->EXP = SaveGameInstance->SaveParameter.playerEXP;
			                     MyCharacter->dataNum = SaveGameInstance->SaveParameter.levelData;
			                     MyCharacter->SetActorTransform(SaveGameInstance->SaveParameter.playerTransform);
			
			                     //FPlatformProcess::Sleep(0.2f);
			                     UE_LOG(LogTemp, Log, TEXT("TaskPlayerState End"));
								 UE_LOG(LogTemp, Warning, TEXT("LoadClear"));
		                     }, TaskOpenLevel
		);
TaskPlayerState.Wait();
		clearLoad = true;
	}
	else
	{
		clearLoad = false;
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
