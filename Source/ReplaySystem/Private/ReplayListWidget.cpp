// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplayListWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ReplaySystemTypes.h"
#include "Components/ListView.h"

#include "ReplayGameInstance.h"

void UReplayListWidget::OnListViewItemSelectionChanged(UObject* Object)
{
	UItemData* ItemData = Cast<UItemData>(Object);
	if (!ItemData)
	{
		return;
	}
	SelectedReplayName = ItemData->ReplayName;
}

void UReplayListWidget::OnStartButtonClicked()
{
	if(UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		if(UReplayGameInstance* ReplayGameInstance = Cast<UReplayGameInstance>(GameInstance))
		{
			ReplayGameInstance->StartReplay(SelectedReplayName);
		}
	}
}

void UReplayListWidget::OnQuitButtonClicked()
{
	OnQuitBtnClick.Broadcast();
}

void UReplayListWidget::GetFilesInDirectory(const FString& Directory, const FString& Extension, TArray<FString>& OutFiles)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	TArray<FString> Files;
	PlatformFile.FindFiles(Files, *Directory, nullptr);
	for (const FString& File : Files)
	{
		OutFiles.Add(FPaths::GetBaseFilename(File));
	}
}

void UReplayListWidget::UpdateListViewData()
{
	ListView->ClearListItems();
	TArray<FString> Files;
	GetFilesInDirectory(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Demos")), "*/*.replay", Files);
	for(auto Temp : Files)
	{
		UItemData* ItemData = NewObject<UItemData>();
		ItemData->ReplayName = Temp;
		ListView->AddItem(ItemData);
	}
}

void UReplayListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ListView->OnItemSelectionChanged().AddUObject(this, &UReplayListWidget::OnListViewItemSelectionChanged);
	StartReplayButton->OnClicked.AddDynamic(this, &UReplayListWidget::OnStartButtonClicked);
	QuitReplayButton->OnClicked.AddDynamic(this, &UReplayListWidget::OnQuitButtonClicked);
	UpdateListViewData();
}

void UReplayListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UReplayListWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
