// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoleBase.generated.h"

enum class ESkillType : uint8;
struct FRoleProperty;
struct FSkillConfig;
class URolePropertyComponent;

struct FRoleSkill
{
	float Interval = 0.f;
	int NextSkill = 0;
	/*  £”‡¿‰»¥ ±º‰ */
	TArray<float> SkillCD = {};
	TArray<FSkillConfig> SkillConfigArray = {};
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRoleUseSkill, ESkillType, TObjectPtr<ARoleBase>, TObjectPtr<ARoleBase>);


UCLASS()
class MONSTERTIDE_API ARoleBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARoleBase();

	void InitRole(FRoleProperty* RoleProperty);

	void RemoveRole();

	bool IsDead();

	FOnRoleUseSkill OnRoleUseSkill;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<URolePropertyComponent> RolePropertyComponent;

	void ChangeHP(float Value);
	void ChangeMP(float Value);

protected:
	virtual void BeginPlay() override;

	FRoleProperty* CurRoleProperty;

 	TArray<TObjectPtr<AActor>> GetTargetWithinRange(ECollisionChannel Channel);

	FRoleSkill RoleSkill = FRoleSkill();

	virtual float UseSkill();
	int GetNextSkill();

private:
	void SkillTiming(float DeltaTime);

	void RefreshPropertyPosition();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
