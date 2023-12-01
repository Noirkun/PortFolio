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
	*/
	UFUNCTION(BlueprintCallable, Category = "LevelFuncLibrary", meta=(WorldContext="WorldContextObject"))
	static void AsyncOpenLevel(const UObject* WorldContextObject,const TSoftObjectPtr<UWorld> Level,double FadeTime=1.0f);
	
	
};
