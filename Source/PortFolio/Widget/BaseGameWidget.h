// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "BaseGameWidget.generated.h"

/**
 * ゲーム内のUIを作るベースのクラス
 */
UCLASS(Abstract)
class PORTFOLIO_API UBaseGameWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	
	virtual void NativeConstruct() override;

	void FadeIn();
	void FadeOut();

protected:

	//TitleGameWidgetなどでエラーが起きるので修正が必要（Bind対象がない）
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInAnimation=nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOutAnimation=nullptr;	
	
	virtual bool Initialize() override;
	//関数をバインドする関数
	virtual void BindFunctions() PURE_VIRTUAL(UBaseGameWidget::BindFunctions, );


private:
	FString FadeInWidgetPath = "PortFolio/Content/Widget/BP_Fade_c";
	TSubclassOf<UUserWidget> FadeWidget;
};
