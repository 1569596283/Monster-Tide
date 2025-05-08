// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Game.generated.h"


class UScrollBox;
struct FRoleProperty;
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_HeroItem> HeroItemClass;

public:
	virtual void NativeOnInitialized() override;

	void RefreshHeros();

private:
	void AddHeroItem(FRoleProperty& rp);

	void RemoveHeroItem();
};
