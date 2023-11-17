// Fill out your copyright notice in the Description page of Project Settings.


#include "../DataTable/PlayerStatusDataAsset.h"

void UPlayerStatusDataAsset::Import()
{
#if WITH_EDITORONLY_DATA
    if (!DataTable ||
        !DataTable->GetRowStruct()->IsChildOf(FCharacterLevelStatus::StaticStruct()))
    {
        return;
    }

    Data.Empty();
    auto Names = DataTable->GetRowNames();

    for (int i = 0; i < Names.Num(); i++)
    {
	    auto record = DataTable->FindRow<FCharacterLevelStatus>(Names[i], FString());

        FPlayerStatusStruct asset(record->Level,record->HP, record->Attack,record->EXP);

        /*
        asset.playerLevel = record->Level;
        asset.playerMaxHealth = record->HP;
        asset.attackValue = record->Attack;
        asset.playerMaxEXP = record->EXP;
*/
        
        Data.Add(asset);
    }

#endif

}
