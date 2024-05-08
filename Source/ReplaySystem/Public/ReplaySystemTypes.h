// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/BlueprintSupport.h"
#include "ReplaySystemTypes.generated.h"

/**
 * 
 */
 UCLASS()
class REPLAYSYSTEM_API UItemData : public UObject
{
	GENERATED_BODY()

public:
	FString ReplayName;
};
