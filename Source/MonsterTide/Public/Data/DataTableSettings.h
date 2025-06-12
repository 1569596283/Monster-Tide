// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DataTableSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Game Data Settings"))
class MONSTERTIDE_API UDataTableSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// 直接获取数据表格的便捷方法（可选）
	UFUNCTION(BlueprintCallable, Category = "Data")
	UDataTable* GetGameEnemyDataTable() const;
	UFUNCTION(BlueprintCallable, Category = "Data")
	UDataTable* GetEnemyPropertyDataTable() const;
	UFUNCTION(BlueprintCallable, Category = "Data")
	UDataTable* GetHeroPropertyDataTable() const;
	UFUNCTION(BlueprintCallable, Category = "Data")
	UDataTable* GetLevelDataTable() const;
	UFUNCTION(BlueprintCallable, Category = "Data")
	UDataTable* GetSkillDataTable() const;

protected:
	UPROPERTY(Config, EditAnywhere, Category = "Data Tables", meta = (AllowedClasses = "DataTable"))
	TSoftObjectPtr<UDataTable> GameEnemyDataTable;
	UPROPERTY(Config, EditAnywhere, Category = "Data Tables", meta = (AllowedClasses = "DataTable"))
	TSoftObjectPtr<UDataTable> EnemyPropertyDataTable;
	UPROPERTY(Config, EditAnywhere, Category = "Data Tables", meta = (AllowedClasses = "DataTable"))
	TSoftObjectPtr<UDataTable> HeroPropertyDataTable;
	UPROPERTY(Config, EditAnywhere, Category = "Data Tables", meta = (AllowedClasses = "DataTable"))
	TSoftObjectPtr<UDataTable> LevelDataTable;
	UPROPERTY(Config, EditAnywhere, Category = "Data Tables", meta = (AllowedClasses = "DataTable"))
	TSoftObjectPtr<UDataTable> SkillDataTable;
};
