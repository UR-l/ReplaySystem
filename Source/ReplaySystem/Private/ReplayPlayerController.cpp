// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayPlayerController.h"
#include "Engine/DemoNetDriver.h"
#include "Kismet/GameplayStatics.h"
#include "ReplayControlWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/WorldSettings.h"

void AReplayPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ReplayWidgetPtr = nullptr;
	DemoNetDriverPtr = nullptr;
	FindDemoNetDriver();
	if (DemoNetDriverPtr->IsPlaying() && ReplayControlWidgetObject.Get())
	{
		SetShowMouseCursor(true);
		ReplayWidgetPtr = CreateWidget<UReplayControlWidget>(GetWorld(), ReplayControlWidgetObject);
		ReplayWidgetPtr->SetProgressMaxValue(GetReplayTotalTime());
		ReplayWidgetPtr->AddToViewport();

		ReplayWidgetPtr->OnQuitReplatEvent.BindUObject(this, &AReplayPlayerController::QuitPlayReplay);
		ReplayWidgetPtr->RestartPlayButtonEvent.BindUObject(this, &AReplayPlayerController::RestartPlayReplay);
		ReplayWidgetPtr->OnGotoTimeInSecondsEvent.BindUObject(this, &AReplayPlayerController::GotoTimeInSeconds);
		ReplayWidgetPtr->OnReplayStateEvent.BindUObject(this, &AReplayPlayerController::SetCurrentReplayPausedState);
		ReplayWidgetPtr->OnReplayPlayRateEvent.BindUObject(this, &AReplayPlayerController::SetCurrentReplayPlayRate);
	}
}

void AReplayPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (DemoNetDriverPtr->IsPlaying() && ReplayWidgetPtr && DemoNetDriverPtr)
	{
		ReplayWidgetPtr->UpdateCurentTime(GetReplayCurrentTime());
	}
}

void AReplayPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool AReplayPlayerController::SetCurrentReplayPausedState(bool bDoPause)
{
	if (DemoNetDriverPtr)
	{
		AWorldSettings* WorldSettings = GetWorldSettings();

		if (bDoPause)
		{
			WorldSettings->SetPauserPlayerState(PlayerState);
			return true;
		}

		WorldSettings->SetPauserPlayerState(NULL);
		return false;
	}
	return false;
}

void AReplayPlayerController::SetCurrentReplayPlayRate(float PlayRate /*= 1.0f*/)
{
	if (DemoNetDriverPtr)
	{
		GetWorld()->GetWorldSettings()->DemoPlayTimeDilation = PlayRate;
	}
}

void AReplayPlayerController::QuitPlayReplay()
{
	if (ExitOpenLevelObject.IsPending())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), ExitOpenLevelObject);
	}
}

void AReplayPlayerController::RestartPlayReplay()
{
	if (DemoNetDriverPtr)
	{
		DemoNetDriverPtr->GotoTimeInSeconds(0.0f);
	}
}

void AReplayPlayerController::GotoTimeInSeconds(float Seconds)
{
	if (DemoNetDriverPtr)
	{
		DemoNetDriverPtr->GotoTimeInSeconds(Seconds);
	}
}

float AReplayPlayerController::GetReplayTotalTime()
{
	if (DemoNetDriverPtr)
	{
		return DemoNetDriverPtr->GetDemoTotalTime();
	}
	return 0;
}

float AReplayPlayerController::GetReplayCurrentTime()
{
	if (DemoNetDriverPtr)
	{
		return DemoNetDriverPtr->GetDemoCurrentTime();
	}
	return -1;
}

bool AReplayPlayerController::GetIsReplay()
{
	if (DemoNetDriverPtr)
	{
		return DemoNetDriverPtr->IsPlaying();
	}
	return false;
}

void AReplayPlayerController::FindDemoNetDriver()
{
	if (UWorld* World = GetWorld())
	{
		DemoNetDriverPtr = World->GetDemoNetDriver();
	}
}
