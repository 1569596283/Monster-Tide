// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_StartGame.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_StartGame : public UUserWidget	
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	TObjectPtr<UButton> Btn_Start;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Continue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Exit;

	UFUNCTION()
	void OnStartCilcked();

	UFUNCTION()
	void OnContinueCilcked();

	UFUNCTION()
	void OnExitCilcked();

public:
	virtual void NativeOnInitialized() override;
};
