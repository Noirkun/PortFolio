// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSubsystemManager.h"
#include "Async/Async.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void ULevelSubsystemManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LatentAction.CallbackTarget = this;
	LatentAction.ExecutionFunction = "Completed";    // <- 完了時に呼び出される関数名を設定
	LatentAction.UUID = 1;
	LatentAction.Linkage = 0;
}




void ULevelSubsystemManager::Completed()
{
	Complete = true;

}

void ULevelSubsystemManager::LoadLevel(const FName& level)
{
	Complete = false;
	UGameplayStatics::LoadStreamLevel( this, level, false, false, LatentAction );

}

void ULevelSubsystemManager::UnloadLevel(const FName& level)
{
	Complete = false;
	UGameplayStatics::UnloadStreamLevel( this, level, LatentAction, false );

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

