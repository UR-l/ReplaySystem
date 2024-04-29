// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayGameInstance.h"

void UReplayGameInstance::StartRecoring(const FString& ReplayName, const FString& FriendlyReplayName)
{
	if (ReplayName.IsEmpty() || FriendlyReplayName.IsEmpty())
	{
		StartRecordingReplay(RecordingName, FriendlyRecordingName);
	}
	else
	{
		RecordingName = ReplayName;
		FriendlyRecordingName = FriendlyReplayName;
		StartRecordingReplay(RecordingName, FriendlyRecordingName);
	}
}

void UReplayGameInstance::StopRecoding()
{
	StopRecordingReplay();
}

void UReplayGameInstance::StartReplay(const FString& ReplayName)
{
	if (ReplayName.IsEmpty() && !RecordingName.IsEmpty())
	{
		PlayReplay(RecordingName);
	}
	else
	{
		PlayReplay(ReplayName);
	}
}
