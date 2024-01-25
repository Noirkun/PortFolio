// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SavePointBase.generated.h"

// セーブポイントのActorクラス
UCLASS()
class PORTFOLIO_API ASavePointBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavePointBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// TriggerBoxのOverlapBeginイベント
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// TriggerBoxのOverlapEndイベント
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// セーブポイントのUIを表示
	void ShowWidget();

	// セーブポイントのUIを非表示
	void HideWidget();
	
private:

	// キー入力を有効にする
	void EnableKeyInput();

	// キー入力を無効にする
	void DisableKeyInput();

	// キー入力を受け付ける
	void PressKeyEvent();
	
	// セーブポイントの名前
	UPROPERTY(EditAnywhere, Category = "SavePoint")
	FString SavePointName = "SavePoint";

	// キー表示のUI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> KeyWidgetClass;

	// キー表示のUI
	UPROPERTY()
	UUserWidget* KeyWidget;

	// セーブポイントのUI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> SavePointClass;

	// セーブポイントのUI
	UPROPERTY()
	UUserWidget* SavePointWidget;

	
	// TriggerBox
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	// セーブポイントに最初に触れたかどうか
	UPROPERTY(VisibleAnywhere, Category = "SavePoint")
	bool bIsFirstTouch = false;
};