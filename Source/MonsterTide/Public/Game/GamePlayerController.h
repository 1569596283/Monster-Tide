// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


class UUI_Game;
class UUI_Settlement;
/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;

	void OpenSettlementUI(bool Victory);

	void OpenGameUI(FString LevelName);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Game> UI_GameClass;
	UPROPERTY()
	TObjectPtr<UUI_Game> UI_Game;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Settlement> UI_SettlementClass;
	UPROPERTY()
	TObjectPtr<UUI_Settlement> UI_Settlement;


};
