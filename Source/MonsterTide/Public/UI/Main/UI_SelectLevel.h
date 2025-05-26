// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_SelectLevel.generated.h"


enum class ELevelType :uint8;
class UButton;
class UCanvasPanel;
class UScrollBox;
class UUI_LevelItem;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_SelectLevel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Return;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Classic;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CP_Mode;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CP_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScrollBox> SB_Level;

	UFUNCTION()
	void OnBtnReturnClicked();
	UFUNCTION()
	void OnBtnClassicClicked();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_LevelItem> LevelItemClass;

private:
	ELevelType CurLevelType;
	void SetScrollLevelByType(ELevelType Type);

	TArray<UUI_LevelItem*> LevelItemArr;
};
