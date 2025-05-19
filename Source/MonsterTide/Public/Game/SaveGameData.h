// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

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

	int GetCurLevel() const;
	void SetCurLevl(int Level);

	void SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr);


protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroArr;

	UPROPERTY(BlueprintReadOnly)
	int CurLevel = 0;
};
