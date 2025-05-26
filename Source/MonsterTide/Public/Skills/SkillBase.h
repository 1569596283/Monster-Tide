// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

enum class ESkillType :uint8;
struct FSkillConfig;
class ARoleBase;

UCLASS()
class MONSTERTIDE_API ASkillBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkillBase();

	virtual void InitSkill(ESkillType Type,float Damage ,TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime);

	FVector TargetLocation;
	FSkillConfig* SkillConfig;
	TObjectPtr<ARoleBase> TargetRole;
	TObjectPtr<ARoleBase> UserRole;
	float SkillDamage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
