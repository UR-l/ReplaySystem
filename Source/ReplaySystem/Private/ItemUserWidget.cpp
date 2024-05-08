// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUserWidget.h"
#include "ReplaySystemTypes.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UItemUserWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UItemData* ItemData = Cast<UItemData>(ListItemObject);

	ItemData->ReplayName;

	BgImage->SetVisibility(ESlateVisibility::Collapsed);
	NameTextBlock->SetText(FText::FromString(ItemData->ReplayName));
}

void UItemUserWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	BgImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}