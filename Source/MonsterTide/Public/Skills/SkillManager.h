// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SkillManager.generated.h"

class ARoleBase;
enum class ESkillType : uint8;

/**
 *
 */
UCLASS()
class MONSTERTIDE_API USkillManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitSkill();

private:
	void RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target);
};
