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
	AEnemyBase();

	void InitEnemy(int Path, int Damage,float Exp);

	int GetDamage() const;
	int GetEnemyExp() const;
	/* 获得距离终点的剩余路程 */
	float GetRemainDistance() const;

	FOnEnemyDead OnEnemyDead;
	FOnEnemyArrived OnEnemyArrived;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Dead() override;

private:
	TObjectPtr<USplineComponent> SplineComponent;
	float Distance = 0.f;
	int CurDamage = 1;
	float EnemyExp = 10.f;

	void RemoveRole();

	void Move(float DeltaTime);

};
