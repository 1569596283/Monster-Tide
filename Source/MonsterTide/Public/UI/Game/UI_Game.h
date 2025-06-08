// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Game.generated.h"


class UScrollBox;
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_HeroItem> HeroItemClass;

public:
	virtual void NativeOnInitialized() override;

	void RefreshHeros();

	void InitGameUI(FString LevelName);

	void RefreshEnemyProperss(float Percent);
private:
	void AddHeroItem(TObjectPtr<URoleAttribute> RA);

	//void RemoveHeroItem();
};
