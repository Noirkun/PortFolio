// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameWidget.h"

#include "Components/Button.h"


void UBaseGameWidget::NativeConstruct()
{
	static ConstructorHelpers::FObjectFinder<UClass> BP_Fade(*FadeInWidgetPath);
	FadeWidget = BP_Fade.Object;
	if (FadeWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("FadeWidget"));
	}
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UBaseGameWidget::NativeConstruct"));
	BindFunctions();
}

void UBaseGameWidget::FadeIn()
{
	//FadeWidgetを作成して、FadeInAnimationを再生する
	UUserWidget* FadeWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), FadeWidget);
	if (FadeWidgetInstance)
	{
		FadeWidgetInstance->AddToViewport();
	}
	this->PlayAnimation(FadeInAnimation);
}

void UBaseGameWidget::FadeOut()
{
	this->PlayAnimation(FadeOutAnimation);
}

bool UBaseGameWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	UE_LOG(LogTemp, Warning, TEXT("Initialize"));


	return true;
}




