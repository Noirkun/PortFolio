// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Struct/PlayerStatusStruct.h"
#include "SaveParmeterStruct.generated.h"
/**
 * 
 */
//セーブ・ロードする変数の構造体
USTRUCT(BlueprintType)
struct FSaveParmeterStruct
{
	GENERATED_BODY()

	/*
	 *	名前
		*現在のレベル
		現在のマップ
		経験値数
		最大体力
		現在の体力
		攻撃力
		プレイ時間
		プレイヤーの位置
		天気・時間
		アイテムスロット（あれば）
		畑
	 * 
	 */
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "SaveParameter")
	FString level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveParameter")
	FPlayerStatusStruct playerStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveParameter")
	double playerEXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveParameter")
	int32 levelData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveParameter")
	FTransform playerTransform;


	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveParameter")
//	double playTime;


	/*
	天気・時間
	アイテムスロット（あれば）
	畑
	*/

	
};