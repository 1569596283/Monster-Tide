// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Recruit.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_Recruit : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void RefreshInfo();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Return;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Recruit;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_FairyStone;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_RecruitFS;
	

	UFUNCTION()
	void OnBtnReturnClicked();
	UFUNCTION()
	void OnBtnRecruitClicked();

private:
	UPROPERTY()
	int RecruitCost = 200;
};
