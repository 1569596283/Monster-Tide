// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RolePropertyComponent.generated.h"


UENUM(BlueprintType)
enum class ERoleType :uint8 {
	Hero,
	Enemy
};

USTRUCT(BlueprintType)
struct FRolePrperty :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type;

	UPROPERTY(EditDefaultsOnly)
	float MaxHP;

	UPROPERTY(EditDefaultsOnly)
	float HP;

	UPROPERTY(EditDefaultsOnly)
	float MaxMP;

	UPROPERTY(EditDefaultsOnly)
	float MP;

	UPROPERTY(EditDefaultsOnly)
	float Attack;

	UPROPERTY(EditDefaultsOnly)
	float Defense;
};


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

	FRolePrperty* RoleProperty;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool InitProperty(FName rowName);
};
