// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeScreenSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameSession.h"
#include "PortFolio/Widget/Fade/SFadeScreen.h"
#include "Struct/FadeScreenStruct.h"

void UFadeScreenSubsystem::AddFadeScreen(const FFadeScreenParams& FadeParams, const APlayerController* OwningPlayer,
                                         const int32 ZOrder)
{
	const int32 ControllerID = GetPlayerControllerID(OwningPlayer);
	if (FadeWidgetsForID.Contains(ControllerID))
	{
		RemoveFadeWidget(OwningPlayer, ControllerID);
	}
	FFadeScreenDelegate FadeScreenDelegate;

	if (FadeParams.ToColor.A <= 0.0f)
	{
		FadeScreenDelegate.BindUObject(this, &UFadeScreenSubsystem::RemoveFadeWidget, ControllerID);
	}
	
	TSharedRef<SFadeScreen> FadeScreen = SNew(SFadeScreen).FadeParams(FadeParams).OnFadeFinished(FadeScreenDelegate);

	if (UGameViewportClient* GameViewport = GetWorld() -> GetGameViewport())
	{
		if(OwningPlayer)
		{
			GameViewport -> AddViewportWidgetForPlayer(OwningPlayer -> GetLocalPlayer(), FadeScreen, ZOrder);
		}
		else
		{
			GameViewport -> AddViewportWidgetContent(FadeScreen, ZOrder + 10);
		}
	}
	FadeWidgetsForID.Emplace(ControllerID, FadeScreen);
	FadeScreen -> StartFade();
}

void UFadeScreenSubsystem::RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerID)
{
	TSharedRef<SWidget> FadeWidget = FadeWidgetsForID[ControllerID].Pin().ToSharedRef();
	FadeWidgetsForID.Remove(ControllerID);

	if (UGameViewportClient* GameViewport = GetWorld()->GetGameViewport())
	{
		if (OwningPlayer)
		{
			GameViewport->RemoveViewportWidgetForPlayer(OwningPlayer->GetLocalPlayer(), FadeWidget);
		}
		else
		{
			GameViewport->RemoveViewportWidgetContent(FadeWidget);
		}
	}
}

void UFadeScreenSubsystem::RemoveFadeWidget(const int32 ControllerID)
{
	RemoveFadeWidget(GetPlayerControllerFromID(ControllerID), ControllerID);
}

int32 UFadeScreenSubsystem::GetPlayerControllerID(const APlayerController* PlayerController) const
{
	if (PlayerController)
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			return LocalPlayer->GetControllerId();
		}
	}

	
	return 0x80000000;
}

APlayerController* UFadeScreenSubsystem::GetPlayerControllerFromID(const int32 ControllerID) const
{
	// Invalid controller ID
	if (ControllerID == 0x80000000)
	{
		return nullptr;
	}

	if (const UWorld* World = GetWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();

			if (GetPlayerControllerID(PlayerController) == ControllerID)
			{
				return PlayerController;
			}
		}
	}

	return nullptr;
}

void UFadeScreenSubsystem::AddFadeInScreen(const double Time, const FLinearColor& FromColor,
                                           const FFadeScreenDelegate& OnFinished, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	FFadeScreenParams FadeParams(Time, FromColor, FLinearColor::Transparent, OnFinished);
	AddFadeScreen(FadeParams, OwningPlayer, ZOrder);
}

void UFadeScreenSubsystem::AddFadeOutScreen(const double Time, const FLinearColor& ToColor,
	const FFadeScreenDelegate& OnFinished, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	FFadeScreenParams FadeParams(Time, FLinearColor::Transparent, ToColor, OnFinished);
	AddFadeScreen(FadeParams, OwningPlayer, ZOrder);
}


