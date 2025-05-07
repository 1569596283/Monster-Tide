// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


class UUI_Game;
/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Game> UI_GameClass;

public:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UUI_Game> UI_Game;
};
