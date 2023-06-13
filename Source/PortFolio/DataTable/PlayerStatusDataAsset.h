#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Struct/PlayerStatusStruct.h"
#include "PlayerStatusDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPlayerStatusDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, Category = "PlayerStatus")
        UDataTable* DataTable;
#endif
    UFUNCTION(meta = (CallInEditor = "true"))
        void Import();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TArray<FPlayerStatusStruct> Data;
	
};
