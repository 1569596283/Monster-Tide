// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManager.generated.h"


enum class ELevelType :uint8;
class USaveGameData;
struct FRoleProperty;
/**
 *
 */
UCLASS()
class MONSTERTIDE_API USaveManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SaveGameData(FString Name);

	void InitSaveData();

	bool ReadSaveData(FString Name);

	const TArray< FRoleProperty >& GetHeroArray() const;

	int GetLastLevel(ELevelType Type);
	void SetLastLevel(ELevelType Type, int Level);

	void SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr);


private:
	UPROPERTY()
	TObjectPtr<USaveGameData> GameData;
};
