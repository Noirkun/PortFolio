// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

// データテーブル用のアイテムのデータをまとめた構造体
USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, meta = (ToolTip = "Itemの名前"))
	FString ItemName;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Itemの値段"))
	int32 ItemPrice;
	
};

//アイテムのデータアセットの１レコードに当たる構造体
USTRUCT(BlueprintType)
struct FItemDataAssetRecord
{
	GENERATED_BODY()

	FORCEINLINE FItemDataAssetRecord(FString _itemName="None", int32 _itemPrice=0);

		UPROPERTY(EditAnywhere, meta = (ToolTip = "Itemの名前"))
	FString ItemName;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Itemの値段"))
	int32 ItemPrice;
	
};

FORCEINLINE FItemDataAssetRecord::FItemDataAssetRecord(FString _itemName, int32 _itemPrice)
{
	ItemName = _itemName;
	ItemPrice = _itemPrice;
}
