// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoleBase.generated.h"

enum class ESkillType : uint8;
enum class ERoleAnimState : uint8;
struct FRoleProperty;
struct FSkillConfig;
class URolePropertyComponent;
class URoleAttribute;
class URoleAnimInstance;

struct FRoleSkill
{
	float Interval = 0.f;
	int NextSkill = 0;
	/*  £”‡¿‰»¥ ±º‰ */
	TArray<float> SkillCD = {};
	TArray<FSkillConfig> SkillConfigArray = {};
};

DECLARE_MULTICAST_DELEGATE_FourParams(FOnRoleUseSkill, ESkillType, float,TObjectPtr<ARoleBase>, TObjectPtr<ARoleBase>);


UCLASS()
class MONSTERTIDE_API ARoleBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARoleBase();

	void InitRole(TObjectPtr<URoleAttribute> RA);

	void RemoveRole();

	bool IsDead();

	FOnRoleUseSkill OnRoleUseSkill;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<URolePropertyComponent> RolePropertyComponent;

	float OnHit(float Damage , TObjectPtr<ARoleBase> Source);
	TObjectPtr<ARoleBase> Killer;

	const FRoleProperty* GetRoleProperty();
protected:
	FRoleSkill RoleSkill = FRoleSkill();
	UPROPERTY()
	TObjectPtr<URoleAttribute> RoleAttribute;

	virtual void BeginPlay() override;
 	TArray<TObjectPtr<AActor>> GetTargetWithinRange(ECollisionChannel Channel);

	virtual float UseSkill();

	int GetNextSkill();

	virtual void Dead();

	TObjectPtr<URoleAnimInstance> RoleAnimInstance;

private:
	void SkillTiming(float DeltaTime);


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
