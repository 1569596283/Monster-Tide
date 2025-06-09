// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

enum class ELevelType :uint8;
enum class ERoleType :uint8;
struct FRoleProperty;
struct FHeroInfo;


/**
 *
 */
UCLASS()
class MONSTERTIDE_API USaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	TArray<FHeroInfo> GetHeroInfoArray();
	FHeroInfo GetHeroInfo(FString ID);
	FString ChangeHeroName(FString ID, FString NewName);

	FHeroInfo* AddHero(ERoleType Type, int Level);

	int GetFairyStone() const;
	bool ChangeFairyStone(int Value);

	int GetLastLevel(ELevelType Type);
	void SetLastLevl(ELevelType Type, int Level);

	void RefreshHeroInfo(FHeroInfo HeroInfo);

protected:
	UPROPERTY(BlueprintReadOnly)
	int HeroIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHeroInfo> HeroInfoArr;

	UPROPERTY(BlueprintReadOnly)
	TMap<ELevelType, int> LastLevelMap;

	UPROPERTY()
	int FairyStone = 100;
};
