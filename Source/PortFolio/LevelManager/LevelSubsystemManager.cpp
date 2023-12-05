// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSubsystemManager.h"
#include "Async/Async.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Containers/Ticker.h"
#include "Kismet/GameplayStatics.h"
#include "PortFolio/PortFolioCharacter.h"
#include "PortFolio/GameModes/FarmWorldSettings.h"
#include "PortFolio/SaveGame/SaveSystem.h"

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
	
	if (LoadingScreenWidget->GetParent() != nullptr && LoadingScreenWidget->GetParent()->IsA<UGameViewportClient>())
	{
		LoadingScreenWidget->RemoveFromParent();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadingScreenWidget is not in viewport"));
	}
	//完了したらLevelを移動する。
	UGameplayStatics::OpenLevel( this, LoadLevelName );

	Complete = true;
	
}

void ULevelSubsystemManager::UnLevelLoadCompleted()
{
	UGameplayStatics::LoadStreamLevel( this, LoadLevelName, false, false, LoadLatentAction );
}

//非同期でレベルをロードする関数(LevelFuncLibraryに移動済み)
/*
void ULevelSubsystemManager::AsyncOpenLevel(ELevelNamesType Level)
{
	
	UGameManager* GameManager = GetWorld()->GetGameInstance<UGameManager>();

	FString LevelName = "Stage02";
	//エラーが起きてる。
	if(GameManager)
	{
		TArray<FName> LevelNames = GameManager->GetLevelNames();

		UE_LOG(LogTemp, Warning, TEXT("LoadLevelName=%d"), LevelNames.Num());
		
		for(auto LevelNameSlot : LevelNames)
		{
			UE_LOG(LogTemp, Warning, TEXT("LoadLevelName=%s"), *LevelNameSlot.ToString());
		
		}
		
		LevelName = LevelNames[static_cast<int32>(Level)].ToString();
		UE_LOG(LogTemp, Warning, TEXT("LevelName=%s"), *LevelName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotGameManager"));
		return;
	}
	

	
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
*/

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

	AWorldSettings *WorldSettings = GetWorld()->GetWorldSettings();
	AFarmWorldSettings *FarmWorldSettings = Cast<AFarmWorldSettings>(WorldSettings);
	if (FarmWorldSettings)
	{
		UUserWidget *Widget = FarmWorldSettings->GetLoadingWidget().GetDefaultObject();
		if (Widget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget is %s"), *Widget->GetName())
			LoadingScreenWidget = CreateWidget<UUserWidget>(GetWorld(), Widget->GetClass());
			if (LoadingScreenWidget)
			{
				LoadingScreenWidget->AddToViewport();
			}
		}
	}
	
}

bool ULevelSubsystemManager::IsCompleted() const
{
	return Complete;
}

