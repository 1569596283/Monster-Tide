// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_LevelItem.generated.h"

struct FLevelConfig;
class UButton;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_LevelItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void InitLevelConfig(FLevelConfig* LevelCfg);


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Img_Level;


	UFUNCTION()
	void OnBtnLevelClicked();
private:
	int CurLevel;
};
