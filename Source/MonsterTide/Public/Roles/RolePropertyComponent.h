// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RolePropertyComponent.generated.h"


struct FRoleProperty;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MONSTERTIDE_API URolePropertyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URolePropertyComponent();

	UPROPERTY()
	TObjectPtr<UDataTable> DT_RoleProperty;

protected:
	virtual void BeginPlay() override;

	FRoleProperty* RoleProperty;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool InitProperty(FRoleProperty* rp);
};