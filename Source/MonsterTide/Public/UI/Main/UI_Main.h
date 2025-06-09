// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Main.generated.h"


class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_Main : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void RefreshInfo();

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Play;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Hero;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_FairyStone;


	UFUNCTION()
	void OnBtnPlayClicked();
	UFUNCTION()
	void OnBtnHeroClicked();

};
