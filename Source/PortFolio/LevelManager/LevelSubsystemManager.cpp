// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSubsystemManager.h"
#include "Async/Async.h"
#include "Containers/Ticker.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void ULevelSubsystemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadLatentAction.CallbackTarget = this;
	LoadLatentAction.ExecutionFunction = "LevelLoadCompleted";    // <- 完了時に呼び出される関数名を設定
	LoadLatentAction.UUID = 1;
	LoadLatentAction.Linkage = 0;

	UnloadLatentAction.CallbackTarget = this;
	UnloadLatentAction.ExecutionFunction = "LevelLoadCompleted";    // <- 完了時に呼び出される関数名を設定
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

void ULevelSubsystemManager::LoadLevel(const FName& level)
{
	Complete = false;
	UGameplayStatics::UnloadStreamLevel( this, GetWorld()->GetFName(), LoadLatentAction, false );
	LoadLevelName=level;
	
}

bool ULevelSubsystemManager::ShowLevel(const FName& level) const
{
	auto levelstream = UGameplayStatics::GetStreamingLevel( GetWorld(), level );
	check(levelstream != nullptr);
	levelstream->SetShouldBeVisible( true );
	return levelstream->IsLevelVisible();  // 処理簡略の為SetShouldBeVisible関数とIsLevelVisible関数が一緒に実行されていますが分けた方がすっきりします

}

bool ULevelSubsystemManager::HideLevel(const FName& level) const
{
	auto levelstream = UGameplayStatics::GetStreamingLevel( GetWorld(), level );
	check(levelstream != nullptr);
	levelstream->SetShouldBeVisible( false );
	return !levelstream->IsLevelVisible();

}

bool ULevelSubsystemManager::IsCompleted() const
{
	return Complete;
}

