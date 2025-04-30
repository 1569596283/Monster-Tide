// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"


class UUI_StartGame;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_StartGame> UI_StartGameClass;

public:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UUI_StartGame> UI_StartGame;
};
