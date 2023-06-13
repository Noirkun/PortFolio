// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PortFolio/Struct/PlayerStatusStruct.h"
#include "PortFolio/DataTable/PlayerStatusDataAsset.h"
#include "StructFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UStructFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, DisplayName = "LevelUp", Category = "PlayerStatusStruct")
		static void BP_LevelUp(UPARAM(ref)FPlayerStatusStruct& In);

};
