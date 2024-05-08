// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemUserWidget.generated.h"

UCLASS()
class REPLAYSYSTEM_API UItemUserWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* BgImage;
};