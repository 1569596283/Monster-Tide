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

public:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_StartGame> UI_StartGameClass;
	UPROPERTY()
	TObjectPtr<UUI_StartGame> UI_StartGame;
};
