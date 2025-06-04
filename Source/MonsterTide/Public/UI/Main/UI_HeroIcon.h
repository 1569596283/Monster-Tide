// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_HeroIcon.generated.h"

class UButton;
class UTextBlock;
class UImage;
class URoleAttribute;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeroIconClicked, TObjectPtr< URoleAttribute >);


/**	
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_HeroIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	FOnHeroIconClicked OnHeroIconClicked;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Hero;

	TObjectPtr<URoleAttribute> RoleAttribute;
	void InitAttribute(TObjectPtr<URoleAttribute> Attribute);
	void SetState(bool Select);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Img_Hero;

	UFUNCTION()
	void OnBtnHeroIconClicked();
};
