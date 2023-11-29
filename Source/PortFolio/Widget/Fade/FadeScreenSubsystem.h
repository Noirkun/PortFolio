// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/FadeScreenStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FadeScreenSubsystem.generated.h"

class SWidget;
struct FFadeScreenParams;

// Fadeの種類(まだ使用してない)
UENUM(BlueprintType)
enum class FadeType : uint8
{
	FadeIn,
	FadeOut
};

/**
 *  Fadeを行うためのサブシステム
 */
UCLASS()
class PORTFOLIO_API UFadeScreenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	/*
	 * FadeInを行う関数
	 * @param Time Fadeにかかる時間
	 * @param FromColor Fadeの開始色
	 * @param OnFinished Fadeが終了したときに呼ばれるデリゲート
	 * @param OwningPlayer Fadeを行うプレイヤー
	 * @param ZOrder Fadeの描画順
	 */
	void AddFadeInScreen(const double Time=1.0f,
		const FLinearColor& FromColor=FLinearColor::Black,
		const FFadeScreenDelegate& OnFinished=FFadeScreenDelegate(),
		const APlayerController* OwningPlayer=nullptr,
		const int32 ZOrder=0);
	
	/*
	 *	FadeOutを行う関数
	 *	@param Time Fadeにかかる時間
	 *	@param ToColor Fadeの終了色
	 *	@param OnFinished Fadeが終了したときに呼ばれるデリゲート
	 *  @param OwningPlayer Fadeを行うプレイヤー
	 *  @param ZOrder Fadeの描画順
	 */
	void AddFadeOutScreen(const double Time=1.0f,
		const FLinearColor& ToColor=FLinearColor::Black,
		const FFadeScreenDelegate& OnFinished=FFadeScreenDelegate(),
		const APlayerController* OwningPlayer=nullptr,
		const int32 ZOrder=0);

private:
	/*
	 * Fadeを行う関数
	 * @param FadeParams Fadeに必要な項目
	 * @param OwningPlayer Fadeを行うプレイヤー
	 */
	UFUNCTION(BlueprintCallable, Category = "FadeScreen")
	void AddFadeScreen(const FFadeScreenParams& FadeParams, const APlayerController* OwningPlayer = nullptr, const int32 ZOrder = 100);

	void RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerID);
	void RemoveFadeWidget(const int32 ControllerID);

	int32 GetPlayerControllerID(const APlayerController* PlayerController) const;
	APlayerController* GetPlayerControllerFromID(const int32 ControllerID) const;
	TMap<int32, TWeakPtr<SWidget>> FadeWidgetsForID;


	
};
