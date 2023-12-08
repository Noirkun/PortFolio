// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ULevelFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* 非同期で移動するレベル（サブレベル指定が必要）
	@param Level 移動するレベル
	@param FadeTime フェードインとフェードアウトの時間
	@param MoveLevelPointNum WorldSettingsでセットした配列の番号(指定してない場合LevelのデフォルトのTransformにスポーン)
	*/
	UFUNCTION(BlueprintCallable, Category = "LevelFuncLibrary", meta=(WorldContext="WorldContextObject"))
	static void AsyncOpenLevel(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld> Level,double FadeTime=1.0f,const int32 MoveLevelPointNum=0);
	
	inline static bool bLoading = false;
	
};
