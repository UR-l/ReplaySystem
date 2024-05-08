// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplayControlWidget.generated.h"

DECLARE_DELEGATE(FOnRestartReplatEvent);
DECLARE_DELEGATE(FOnQuitReplatEvent);
DECLARE_DELEGATE_RetVal_OneParam(bool, FOnReplayStateEvent, bool);
DECLARE_DELEGATE_OneParam(FOnGotoTimeInSecondsEvent, float);
DECLARE_DELEGATE_OneParam(FOnReplayPlayRateEvent, float);

/**
 * 
 */
UCLASS()
class REPLAYSYSTEM_API UReplayControlWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeDestruct();

public:
	FOnQuitReplatEvent OnQuitReplatEvent;
	FOnReplayStateEvent OnReplayStateEvent;
	FOnRestartReplatEvent RestartPlayButtonEvent;
	FOnGotoTimeInSecondsEvent OnGotoTimeInSecondsEvent;
	FOnReplayPlayRateEvent OnReplayPlayRateEvent;

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void SetProgressMaxValue(float MaxValue);

	UFUNCTION(BlueprintCallable, Category = "Replays")
	void UpdateCurentTime(float CurrentTime);

private:
	bool bPauseReplay = false;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentTimeText;
	
	UPROPERTY(meta = (BindWidget))
	class USlider* ProgressSlider;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TotalTimeText;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* PauseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartPlayButton;
	
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ReplayPlayRateComBox;

	bool bSliderCapture = false;
	
	UFUNCTION()
	void OnQuitButtonClicked();
	
	UFUNCTION()
	void OnPauseButtonClicked();
	
	UFUNCTION()
	void OnRestartPlayButtonClicked();
	
	UFUNCTION()
	void OnReplayPlayRateComBoxChanged();
	
	UFUNCTION()
	void OnSliderCaptureBegin();
	
	UFUNCTION()
	void OnSliderCaptureEnd();
};