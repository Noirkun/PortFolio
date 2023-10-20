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

//SaveGameを取得する
USaveSystem* USaveSubsystem::GetSaveSystem(const FString& SlotName, const int32& SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		return Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex));
	}
	return nullptr;
}

//セーブする際に呼ぶ
void USaveSubsystem::Save(const FString& SlotName, const int32& SlotIndex)
{
	USaveSystem* SaveGame = GetSaveSystem(SlotName, SlotIndex);
	if (SaveGame == nullptr)
	{
		SaveGame = Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	}

	ACharacter* Character=UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0);

	const APortFolioCharacter* MyCharacter=Cast<APortFolioCharacter,ACharacter>(Character);
	
	SaveGame->SaveParameter	={GetWorld(),MyCharacter->playerStatus,MyCharacter->EXP,
		MyCharacter->dataNum,MyCharacter->GetTransform()};
	GameParameter=SaveGame->SaveParameter;
	
	UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, SlotIndex);
	UE_LOG(LogTemp, Warning, TEXT("SaveClear"));
}

//ロードの際に呼ぶ
void USaveSubsystem::Load(const FString& SlotName, const int32& SlotIndex)
{
	USaveSystem* SaveGame = GetSaveSystem(SlotName, SlotIndex);
	
	if (SaveGame != nullptr)
	{
		//レベルの移動を行うとステータスが1からになるので確認
		UGameplayStatics::OpenLevel(GetWorld(),FName(*SaveGame->SaveParameter.level.Get()->GetMapName()));
		
	}

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);
	
	UE_LOG(LogTemp, Warning, TEXT("Loaded EXP: %f"), SaveGame->SaveParameter.playerEXP);
	UE_LOG(LogTemp, Warning, TEXT("Loaded dataNum: %d"), SaveGame->SaveParameter.levelData);

	if (SaveGame != nullptr && MyCharacter != nullptr)
	{
		MyCharacter->playerStatus=SaveGame->SaveParameter.playerStatus;
		MyCharacter->EXP=SaveGame->SaveParameter.playerEXP;
		MyCharacter->dataNum=SaveGame->SaveParameter.levelData;
		MyCharacter->SetActorTransform(SaveGame->SaveParameter.playerTransform);
		UE_LOG(LogTemp, Warning, TEXT("LoadClear"));

	}
}
