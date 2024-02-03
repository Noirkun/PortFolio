

#pragma once

#if WITH_EDITOR
#include "UnrealEd.h"
#endif

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Item/ItemDataStruct.h"
#include "ItemDataAsset.generated.h"



/**
 *  アイテムのデータアセット
 */
UCLASS()
class PORTFOLIO_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//エディターのみで使用する変数
	#if WITH_EDITORONLY_DATA
	//データテーブル
	UPROPERTY(EditAnywhere, Category = "ItemData")
	UDataTable* DataTable;
#endif

	//CSVデータのインポートを行う関数
	UFUNCTION(Category="DataImport",meta = (CallInEditor = "true",ToolTip = "CSVデータのインポート・更新を行う"))
	void Import();

	//データテーブルからデータを取得する変数
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemDataAssetRecord> Data;
	
};
