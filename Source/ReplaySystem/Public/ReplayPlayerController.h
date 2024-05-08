// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ReplayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class REPLAYSYSTEM_API AReplayPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replays")
	TSubclassOf<class UReplayControlWidget> ReplayControlWidgetObject;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replays")
	TSoftObjectPtr<class UWorld> ExitOpenLevelObject;
	
	UFUNCTION(BlueprintCallable, Category = "Replays")
	bool SetCurrentReplayPausedState(bool bDoPause);

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void SetCurrentReplayPlayRate(float PlayRate = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void QuitPlayReplay();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void RestartPlayReplay();
	
	UFUNCTION(BlueprintCallable, Category = "Replays")
	void GotoTimeInSeconds(float Seconds);

	UFUNCTION(BlueprintCallable, Category = "Replays")
	float GetReplayTotalTime();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	float GetReplayCurrentTime();

	UFUNCTION(BlueprintCallable, Category = "Replays")
	bool GetIsReplay();

private:
	int32 PreviousAASetting;
	int32 PreviousMBSetting;
	class UReplayControlWidget* ReplayWidgetPtr;
	class UDemoNetDriver* DemoNetDriverPtr;


	void FindDemoNetDriver();

};
