// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManager.generated.h"



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

	void SetCurLevel(int Level);
	void SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr);
	
private :
	TObjectPtr<USaveGameData> GameData;
};
