// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roles/RoleBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AEnemyBase : public ARoleBase
{
	GENERATED_BODY()
	
public:
	void InitRole(FRoleProperty* RoleProperty);
};
