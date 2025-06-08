// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/RolePropertyData.h"
#include "HeroInfoData.generated.h"


struct FRoleProperty;

/* ”¢–€–≈œ¢ */
USTRUCT(BlueprintType)
struct FHeroInfo
{
	GENERATED_BODY()

	FHeroInfo();

	UPROPERTY(EditDefaultsOnly)
	FString ID;

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type = ERoleType::Role;

	UPROPERTY(EditDefaultsOnly)
	int Level = 1;
	UPROPERTY(EditDefaultsOnly)
	float Exp = 0.f;

	UPROPERTY(EditDefaultsOnly)
	FRoleProperty BaseRoleProperty;
};

FHeroInfo GetRandomHeroInfo(FString ID, ERoleType Type, int Level);