// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayWidget.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"

void UReplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	QuitButton->OnClicked.AddDynamic(this, &UReplayWidget::OnQuitButtonClicked);
	PauseButton->OnClicked.AddDynamic(this, &UReplayWidget::OnPauseButtonClicked);
	RestartPlayButton->OnClicked.AddDynamic(this, &UReplayWidget::OnRestartPlayButtonClicked);

	FScriptDelegate OnSliderCaptureBeginDelegate;
	OnSliderCaptureBeginDelegate.BindUFunction(this, TEXT("OnSliderCaptureBegin"));
	ProgressSlider->OnMouseCaptureBegin.Add(OnSliderCaptureBeginDelegate);

	FScriptDelegate OnSliderCaptureEndDelegate;
	OnSliderCaptureEndDelegate.BindUFunction(this, TEXT("OnSliderCaptureEnd"));
	ProgressSlider->OnMouseCaptureEnd.Add(OnSliderCaptureEndDelegate);

	ReplayPlayRateComBox->AddOption("0.2");
	ReplayPlayRateComBox->AddOption("0.5");
	ReplayPlayRateComBox->AddOption("0.8");
	ReplayPlayRateComBox->AddOption("1.0");
	ReplayPlayRateComBox->AddOption("1.2");
	ReplayPlayRateComBox->AddOption("1.4");
	ReplayPlayRateComBox->AddOption("1.8");
	ReplayPlayRateComBox->AddOption("2.0");
	ReplayPlayRateComBox->SetSelectedOption("1.0");

	FScriptDelegate OnSelectionChangedDelegate;
	OnSelectionChangedDelegate.BindUFunction(this, TEXT("OnReplayPlayRateComBoxChanged"));
	ReplayPlayRateComBox->OnSelectionChanged.Add(OnSelectionChangedDelegate);
}

void UReplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UReplayWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UReplayWidget::SetProgressMaxValue(float MaxValue)
{
	ProgressSlider->SetMaxValue(MaxValue);
	TotalTimeText->SetText(UKismetTextLibrary::Conv_StringToText(FString::SanitizeFloat((int)(MaxValue * 100) / 100.0) + "s"));
}

void UReplayWidget::UpdateCurentTime(float CurrentTime)
{
	CurrentTimeText->SetText(UKismetTextLibrary::Conv_StringToText(FString::SanitizeFloat((int)(CurrentTime * 100) / 100.0) + "s"));
	if (!bSliderCapture)
	{
		ProgressSlider->SetValue(CurrentTime);
	}
}

void UReplayWidget::OnQuitButtonClicked()
{
	OnQuitReplatEvent.ExecuteIfBound();
}

void UReplayWidget::OnPauseButtonClicked()
{
	bPauseReplay = OnReplayStateEvent.Execute(!bPauseReplay);
}

void UReplayWidget::OnRestartPlayButtonClicked()
{
	RestartPlayButtonEvent.ExecuteIfBound();
}

void UReplayWidget::OnReplayPlayRateComBoxChanged()
{
	OnReplayPlayRateEvent.ExecuteIfBound(FCString::Atof(*ReplayPlayRateComBox->GetSelectedOption()));
}

void UReplayWidget::OnSliderCaptureBegin()
{
	bSliderCapture = true;
}

void UReplayWidget::OnSliderCaptureEnd()
{
	OnGotoTimeInSecondsEvent.ExecuteIfBound(ProgressSlider->GetValue());
	bSliderCapture = false;
}
