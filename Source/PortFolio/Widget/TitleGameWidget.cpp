// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameWidget.h"

#include "Kismet/GameplayStatics.h"
#include "PortFolio/SaveGame/SaveSubsystem.h"

void UTitleGameWidget::NativeConstruct()
{


	
	UE_LOG(LogTemp, Warning, TEXT("TitleGameWidget::NativeConstruct"));
	//GetWidgetFromName(TEXT("BPで作ったWidgetの名前を書いていく"))
	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TitleText")));
	StartButton = Cast<UButton>(GetWidgetFromName("Start"));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("Continue")));
	SettingButton = Cast<UButton>(GetWidgetFromName(TEXT("Setting")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("Quit")));
	
	Super::NativeConstruct();
}

void UTitleGameWidget::BindFunctions()
{
	UE_LOG(LogTemp, Warning, TEXT("BindFunctions"));
	if (StartButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindFunctions.StartButton"));
		StartButton->OnClicked.AddDynamic(this, & UTitleGameWidget::OnStartButtonClicked);
	}

	if (ContinueButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindFunctions.ContinueButton"));
		ContinueButton->OnClicked.AddDynamic(this, &UTitleGameWidget::OnContinueButtonClicked);
	}

	if(SettingButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindFunctions.SettingButton"));
		SettingButton->OnClicked.AddDynamic(this, &UTitleGameWidget::OnContinueButtonClicked);
	}

	if (QuitButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindFunctions.QuitButton"));
		QuitButton->OnClicked.AddDynamic(this, &UTitleGameWidget::OnQuitButtonClicked);
	}
}

void UTitleGameWidget::OnStartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_StartButtonClicked"));
	FadeIn();
	if(UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NOW_GAME_NAME,SAVE_SLOT_NOW_GAME_NUM))
	{
		//セーブデータを消すかどうかの確認ダイアログを表示。
		//消すならセーブデータを消してからゲームを開始する　消さないなら確認用のダイアログを閉じる
	}
	else
	{
		//セーブデータがないのでそのままゲームを開始する
		
	}
}

void UTitleGameWidget::OnContinueButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_ContinueButtonClicked"));
}

void UTitleGameWidget::OnSettingButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_SettingButtonClicked"));
}

void UTitleGameWidget::OnQuitButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("CPP_QuitButtonClicked"));
}


