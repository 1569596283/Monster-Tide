// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


class UUI_Main;
class UUI_SelectLevel;
class UUI_Hero;
class UUI_Recruit;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void ShowMainUMG();

	void OpenLevelUMG();
	void CloseLevelUMG();
	void OpenHeroUMG();
	void CloseHeroUMG();
	void OpenRecruitUMG();
	void CloseRecruitUMG();


protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Main> UI_MainClass;
	UPROPERTY()
	TObjectPtr<UUI_Main> UI_Main;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_SelectLevel> UI_SelectLevelClass;
	UPROPERTY()
	TObjectPtr<UUI_SelectLevel> UI_SelectLevel;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Hero> UI_HeroClass;
	UPROPERTY()
	TObjectPtr<UUI_Hero> UI_Hero;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Recruit> UI_RecruitClass;
	UPROPERTY()
	TObjectPtr<UUI_Recruit> UI_Recruit;
};
