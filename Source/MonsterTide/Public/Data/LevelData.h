// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelData.generated.h"

/* Ω«…´ Ù–‘≈‰÷√ */
USTRUCT(BlueprintType)
struct FLevelConfig :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString LevelName = "";

	UPROPERTY(EditDefaultsOnly)
	int HerosNum = 5;

	UPROPERTY(EditDefaultsOnly)
	int HP = 10;

	UPROPERTY(EditDefaultsOnly)
	TArray<int>Enemy = {};
};

FLevelConfig* GetLevelConfig(int Level);