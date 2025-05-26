// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

enum class ELevelType :uint8;
struct FRoleProperty;
/**
 *
 */
UCLASS()
class MONSTERTIDE_API USaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	const TArray<FRoleProperty>& GetHeroArray() const;

	bool AddHero(FRoleProperty* rp);

	int GetLastLevel(ELevelType Type);
	void SetLastLevl(ELevelType Type ,int Level);

	void SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr);


protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroArr;

	UPROPERTY(BlueprintReadOnly)
	TMap<ELevelType, int> LastLevelMap;
};
