#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Struct/PlayerStatusStruct.h"
#include "PlayerStatusDataAsset.generated.h"

/**
 *  プレイヤーのステータスをまとめたデータアセット
 */
UCLASS()
class PORTFOLIO_API UPlayerStatusDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    //エディターのみで使用する変数
#if WITH_EDITORONLY_DATA
    //データテーブル
    UPROPERTY(EditAnywhere, Category = "PlayerStatus")
        UDataTable* DataTable;
#endif

    //CSVデータのインポートを行う関数
    UFUNCTION(Category="DataImport",meta = (CallInEditor = "true",ToolTip = "CSVデータのインポート・更新を行う"))
        void Import();

    //データテーブルからデータを取得する変数
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TArray<FPlayerStatusStruct> Data;
	
};
