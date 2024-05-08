// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReplayGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REPLAYSYSTEM_API UReplayGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReplayGameInstance")
	FString RecordingName = TEXT("Replay");
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReplayGameInstance")
	FString FriendlyRecordingName = TEXT("FriendlyReplay");
	
	UFUNCTION(BlueprintCallable, Category = "ReplayGameInstance")
	void StartRecoring(const FString& ReplayName, const FString& FriendlyReplayName);
	UFUNCTION(BlueprintCallable, Category = "ReplayGameInstance")
	void StopRecoding();
	UFUNCTION(BlueprintCallable, Category = "ReplayGameInstance")
	void StartReplay(const FString& ReplayName);
};
