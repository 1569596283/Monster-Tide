// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roles/RoleBase.h"
#include "HeroBase.generated.h"

class AEnemyBase;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AHeroBase : public ARoleBase
{
	GENERATED_BODY()
	
public:
	AHeroBase();

	virtual void Tick(float DeltaTime) override;

	void RefreshProperty(TObjectPtr<URoleAttribute>  Attribute, int Level, float Exp);

protected:
	virtual float UseSkill() override;

private:
	void LookAtEnemy();

	TObjectPtr<AEnemyBase> GetTargetEnemy();
};
