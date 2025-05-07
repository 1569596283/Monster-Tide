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
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroArr;

	const TArray<FRoleProperty>& GetHeroArray() const;

	bool AddHero(FRoleProperty* rp);
};
