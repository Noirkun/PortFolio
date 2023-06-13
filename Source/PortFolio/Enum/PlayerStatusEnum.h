// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatusEnum.generated.h"

UENUM(BlueprintType)
enum class EPlayerStatusEnum : uint8
{

	//����Ȃ����ǃe���v���I�Ȋ����Ŏc���Ă�B

	PlayerHealth UMETA(DisplayName = "playerHealth"),
	AttackValue UMETA(DisplayName = "playerHealth"),

};