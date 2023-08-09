// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "PlayerStatusStruct.generated.h"


// データテーブル用構造体
USTRUCT()
struct FCharacterLevelStatus : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		double HP;

	UPROPERTY(EditAnywhere)
		int Attack;

	UPROPERTY(EditAnywhere)
		double EXP;

	
};



USTRUCT(BlueprintType)
struct FPlayerStatusStruct {
	
	GENERATED_BODY()

		FORCEINLINE FPlayerStatusStruct();

	UPROPERTY(BlueprintReadOnly)
		FString CharacterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		int32 playerLevel;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	double playerMaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Status")
	int32 attackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		double playerMaxEXP;


};

FORCEINLINE FPlayerStatusStruct::FPlayerStatusStruct()
{
	playerLevel = 1;
	playerMaxHealth = 100;
	attackValue = 10;
	playerMaxEXP=110;
}