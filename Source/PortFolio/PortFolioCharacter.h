// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PortFolio/Struct/PlayerStatusStruct.h"
#include "PortFolioCharacter.generated.h"


UCLASS(config=Game)
class APortFolioCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	APortFolioCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



	UFUNCTION(BlueprintCallable, Category = "PlayerStatus",meta=(ToolTip="EXPをセットする。MaxEXPまで溜まったらLevelUPを行う。"))
		void SetEXP(double InEXP);


	/**
	 * @brief �f�o�b�O�p�E�Ăяo���p
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "LevelUp", Category = "PlayerStatus")
		void LevelUp();

	UFUNCTION(BlueprintCallable, DisplayName = "LevelDown", Category = "PlayerStatus")
		void LevelDown();

		void GetLevelStatus();

private:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "PlayerStatus")
		UDataTable* StatusDataTable;

#endif

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "PlayerStatus")
	FPlayerStatusStruct playerStatus;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category ="PlayerStatus")
	double HP=playerStatus.playerMaxHealth;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "PlayerStatus")
	double EXP = 0;

	UPROPERTY(EditAnywhere,meta=(ClampMin = "1", ClampMax = "10"))
		int32 maxLevel = 10;

	int32 dataNum = 0;

};

