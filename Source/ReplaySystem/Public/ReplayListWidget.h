// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplayListWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitBtnClickEvent);

/**
 * 
 */
UCLASS()
class REPLAYSYSTEM_API UReplayListWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="ReplayListWidget")
	FOnQuitBtnClickEvent OnQuitBtnClick;

private:
	UPROPERTY(meta = (BindWidget))
	class UListView* ListView;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartReplayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitReplayButton;

	FString SelectedReplayName = "";

	UFUNCTION()
	void OnListViewItemSelectionChanged(UObject* Object);
	
	UFUNCTION()
	void OnStartButtonClicked();
	
	UFUNCTION()
	void OnQuitButtonClicked();

	void GetFilesInDirectory(const FString& Directory, const FString& Extension, TArray<FString>& OutFiles);

	void UpdateListViewData();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
};
