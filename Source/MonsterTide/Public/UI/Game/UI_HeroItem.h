// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_HeroItem.generated.h"

class UTextBlock;
class UButton;
class UProgressBar;
class URoleAttribute;
/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_HeroItem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void InitRoleAttribute(TObjectPtr< URoleAttribute > RA);

private:
	TObjectPtr< URoleAttribute > RoleAttribute;

	bool IsSelect = false;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Hero;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Type;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_MP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_EXP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_MP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_EXP;

	UFUNCTION()
	void OnBtnHeroClicked();

	void RefreshLevel(TObjectPtr< URoleAttribute > Attribute, int Level, float Exp);

	/* 根据当前状态和新点击的角色属性设置是否选中 */
	void SetBtnHeroState(TObjectPtr< URoleAttribute > RA);
	/* 根据是否选中设置按钮颜色 */
	UFUNCTION()
	void RefreshBtnHeroState();
	void OnPlaceHero(TObjectPtr< URoleAttribute > RA);
};
