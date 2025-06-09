// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelData.generated.h"

/* ��ɫ���ͣ�����Ӣ�ۺ͵��� */
UENUM(BlueprintType)
enum class ELevelType :uint8 {
	Classic UMETA(DisplayName = "Classic"),
};


/* ��ɫ�������� */
USTRUCT(BlueprintType)
struct FLevelConfig :public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	int Level = 1;

	UPROPERTY(EditDefaultsOnly)
	ELevelType Type = ELevelType::Classic;

	UPROPERTY(EditDefaultsOnly)
	FString LevelName = "";

	UPROPERTY(EditDefaultsOnly)
	int HerosNum = 5;

	UPROPERTY(EditDefaultsOnly)
	int HP = 10;

	UPROPERTY(EditDefaultsOnly)
	int FairyStone = 100;

	UPROPERTY(EditDefaultsOnly)
	TArray<int>Enemy = {};

};

FLevelConfig* GetLevelConfig(int Level);

TArray<FLevelConfig *> GetLevelConfigs(ELevelType Type);