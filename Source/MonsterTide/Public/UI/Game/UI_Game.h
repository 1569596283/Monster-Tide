// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Game.generated.h"


class UScrollBox;
class UButton;
class UWrapBox;
class UCanvasPanel;
class UTextBlock;
class UProgressBar;
class URoleAttribute;
class UUI_HeroItem;
/**
 *
 */
UCLASS()
class MONSTERTIDE_API UUI_Game : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScrollBox> ScrHero;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_Enemy;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_SHSelect;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CP_SelectHeros;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CP_Heros;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_ShowHide;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_HeroCount;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Start;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> WB_Heros;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_HeroItem> HeroItemClass;
	UPROPERTY()
	TArray<TObjectPtr<UUI_HeroItem>> SelectHeroItemArr;


public:
	virtual void NativeOnInitialized() override;

	void InitGameUI(FString LevelName);

	void RefreshEnemyProperss(float Percent);

private:

	void ShowAllHeros();

	UFUNCTION()
	void OnBtnSHSelectClicked();

	UFUNCTION()
	void OnBtnStartClicked();
	/* 初始化选入战场的英雄 */
	void InitHeroItems();

	void OnHeroSelect(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RA);

	void AddHeroItem(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RA);

	void RemoveHeroItem(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RA);

	void RefreshHeroCount();
};
