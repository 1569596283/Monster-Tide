// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManager.generated.h"


enum class ELevelType :uint8;
enum class ERoleType :uint8;
class USaveGameData;
struct FRoleProperty;
struct FHeroInfo;
/**
 *
 */
UCLASS()
class MONSTERTIDE_API USaveManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SaveGameData();
	void SaveGameData(FString Name);

	void InitSaveData();

	bool ReadSaveData(FString Name);

	TArray< FHeroInfo > GetHeroInfoArray();
	FHeroInfo GetHeroInfo(FString ID);
	FString ChangeHeroName(FString ID, FString NewName);

	int GetFairyStone() const;
	bool ChangeFairyStone(int Value);

	int GetLastLevel(ELevelType Type);
	void SetLastLevel(ELevelType Type, int Level);

	void RefreshHeroInfo(FHeroInfo HeroInfo);
	void RefreshHeroInfo(TArray<FHeroInfo> HeroInfoArr);

	FHeroInfo AddRandomHero(ERoleType Type, int Level);

private:
	UPROPERTY()
	TObjectPtr<USaveGameData> GameData;

	UPROPERTY()
	FString DataSlotName = "TestSaveData";
};
