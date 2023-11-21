// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"
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
void USaveSubsystem::SaveGame(bool& clearSave)
{
	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance=Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));

	//プレイヤーを取得
	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0);
	APortFolioCharacter* MyCharacter=Cast<APortFolioCharacter,ACharacter>(Character);

	//セーブする値のセット
	 SaveGameInstance->SaveParameter={GetWorld()->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
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
		
			// レベルをロードして格納（同期処理なので非同期も検討）
			if (GetWorld() -> GetOuter() -> GetPathName() != LevelName)
			{
				UGameInstance* _GameInst = GetWorld() -> GetGameInstance();

				//LevelManagerから非同期ロード用の関数を呼ぶ
				auto LevelManager = _GameInst -> GetSubsystem<ULevelSubsystemManager>();
				LevelManager -> LoadLevel(*LevelName);

				//LoadMapの最後にデータを入れるようにする。
				FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USaveSubsystem::AttachPlayerStatus);
			}
			else
			{
				AttachPlayerStatus(GetWorld());
			}
		
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

void USaveSubsystem::AttachPlayerStatus(UWorld* World=nullptr)
{
		
	const USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, SAVE_SLOT_NUM));
	const FString& LevelName = SaveGameInstance -> SaveParameter.level;
	
	if(GetWorld())
	{
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this -> GetWorld(), 0);
		
		if (Character)
		{
			//Characterが入ってない
			UE_LOG(LogTemp, Log, TEXT("Character=%p"), Character);

			APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

			// プレイヤーに値を割り振る
			MyCharacter -> playerStatus = SaveGameInstance -> SaveParameter . playerStatus;
			MyCharacter -> EXP = SaveGameInstance -> SaveParameter . playerEXP;
			MyCharacter -> dataNum = SaveGameInstance -> SaveParameter . levelData;
			MyCharacter -> SetActorTransform(SaveGameInstance -> SaveParameter . playerTransform);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("LoadClear"));
}
