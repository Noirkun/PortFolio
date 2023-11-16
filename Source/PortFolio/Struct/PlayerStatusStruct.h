// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "PlayerStatusStruct.generated.h"


// データテーブル用のプレイヤーの変数をまとめた構造体
USTRUCT()
struct FCharacterLevelStatus : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, meta = (ToolTip = "プレイヤーのレベル"))
		int Level;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "プレイヤーのHP"))
		double HP;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "プレイヤーの攻撃力"))
		int Attack;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "プレイヤーが持ってる経験値"))
		double EXP;

	
};



USTRUCT(BlueprintType)
struct FPlayerStatusStruct {
	
	GENERATED_BODY()

		FORCEINLINE FPlayerStatusStruct();

	UPROPERTY(BlueprintReadOnly, meta = (ToolTip = "プレイヤーの名前"))
		FString CharacterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (ToolTip = "プレイヤーのレベル"))
		int32 playerLevel;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ToolTip = "プレイヤーのHP"))
	double playerMaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Status", meta = (ToolTip = "プレイヤーの攻撃力"))
	int32 attackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ToolTip = "プレイヤーが持てる経験値"))
		double playerMaxEXP;


};

FORCEINLINE FPlayerStatusStruct::FPlayerStatusStruct()
{
	playerLevel = 1;
	playerMaxHealth = 100;
	attackValue = 10;
	playerMaxEXP=110;
}