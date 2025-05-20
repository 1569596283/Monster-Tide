// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


class UUI_Main;
class UUI_SelectLevel;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void OpenLevelUMG();
	void CloseLevelUMG();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Main> UI_MainClass;
	UPROPERTY()
	TObjectPtr<UUI_Main> UI_Main;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_SelectLevel> UI_SelectLevelClass;
	UPROPERTY()
	TObjectPtr<UUI_SelectLevel> UI_SelectLevel;
};
