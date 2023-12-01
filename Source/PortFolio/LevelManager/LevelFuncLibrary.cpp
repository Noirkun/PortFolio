// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFuncLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"
#include "PortFolio/LevelManager/LevelSubsystemManager.h"
#include "PortFolio/SaveGame/SaveSystem.h"
#include "PortFolio/Widget/Fade/FadeScreenSubsystem.h"

void ULevelFuncLibrary::AsyncOpenLevel(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld> Level,double FadeTime)
{
	// ワールドを取得
	UWorld * World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));
	UE_LOG( LogTemp, Warning, TEXT("LevelName=%s"), *LevelName.ToString() );

	//プレイヤーを取得
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
	APortFolioCharacter* MyCharacter = Cast<APortFolioCharacter, ACharacter>(Character);

	// USaveSystemクラスを取得
	USaveSystem* SaveGameInstance = Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	//セーブする値のセット
	SaveGameInstance->SaveParameter = { World->GetOuter()->GetPathName(),MyCharacter->playerStatus,MyCharacter->EXP,
	   MyCharacter->dataNum,MyCharacter->GetTransform() };

	UE_LOG(LogTemp, Log, TEXT("NowSaveGame"));
	// 現在のプレイヤーのデータをセーブする
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);
	
	if (SaveGameInstance)
	{
		// LevelNameが現在のレベルと同じでない場合のみロードする
		if (World->GetOuter()->GetPathName() != LevelName.ToString())
		{
			// スロットに保存されているレベル以外をロードするときの処理があれば書く
		}
		UGameInstance* _GameInst = World->GetGameInstance();

		auto FadeSubsystem = _GameInst->GetSubsystem<UFadeScreenSubsystem>();
		auto LevelMnaager = _GameInst->GetSubsystem<ULevelSubsystemManager>();
		FFadeScreenDelegate FadeDelegate;

		// フェードアウトが終わったらレベルを移動する処理をバインドしておく
		FadeDelegate.BindLambda([LevelMnaager, LevelName]()
			{
				UE_LOG(LogTemp, Warning, TEXT("MoveLevel"));
				LevelMnaager->LoadLevel(*LevelName.ToString());
			});
		// フェードアウトを行う
		FadeSubsystem->AddFadeOutScreen(FadeTime, FLinearColor::Black, FadeDelegate);

		//LoadMapの最後にデータを入れるようにする。
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([LevelMnaager, FadeSubsystem,FadeTime](UWorld* World)
			{
				LevelMnaager->AttachPlayerStatus(World, SAVE_SLOT_NOW_GAME_NAME, SAVE_SLOT_NOW_GAME_NUM);
				// フェードインを行う
				FadeSubsystem->AddFadeInScreen(FadeTime);
				UE_LOG(LogTemp, Warning, TEXT("Fade LoadClear"));
			});
	}
}
