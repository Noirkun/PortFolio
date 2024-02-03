// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemDataAsset.h"

void UItemDataAsset::Import()
{
#if WITH_EDITORONLY_DATA
	if (!DataTable ||
		!DataTable->GetRowStruct()->IsChildOf(FItemData::StaticStruct()))
	{
		return;
	}

	Data.Empty();
	auto Names = DataTable->GetRowNames();

	for (int i = 0; i < Names.Num(); i++)
	{
		auto record = DataTable->FindRow<FItemData>(Names[i], FString());

		FItemDataAssetRecord asset(record->ItemName, record->ItemPrice);
        
		Data.Add(asset);
	}

#endif
	
}
