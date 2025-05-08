// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

struct FRoleProperty;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UHeroManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void InitHeroProperty();

	const TArray<FRoleProperty>& GetHeroArray() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroPropertyArr;
};
