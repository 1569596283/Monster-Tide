// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roles/RoleBase.h"
#include "EnemyBase.generated.h"

class USplineComponent;
struct FEnemyPropertyConfig;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, TObjectPtr<AEnemyBase>);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyArrived, TObjectPtr<AEnemyBase>);

/**
 *
 */
UCLASS()
class MONSTERTIDE_API AEnemyBase : public ARoleBase
{
	GENERATED_BODY()

public:
	void InitEnemy(int Path, int Level, FEnemyPropertyConfig* EnemyPropertyConfig);

	int GetDamage();

	FOnEnemyDead OnEnemyDead;
	FOnEnemyArrived OnEnemyArrived;

	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<USplineComponent> SplineComponent;
	float Distance = 0.f;
	int Damage = 1;

	void RemoveRole();

	void Move(float DeltaTime);

};
