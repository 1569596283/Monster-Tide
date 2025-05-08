// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RolePropertyComponent.generated.h"


UENUM(BlueprintType)
enum class ERoleType :uint8 {
	Hero	UMETA(DisplayName = "Hero"),
	Enemy	UMETA(DisplayName = "Enemy")
};

USTRUCT(BlueprintType)
struct FRoleProperty :public FTableRowBase
{
	GENERATED_BODY()

	FRoleProperty() {};

	FRoleProperty(const FRoleProperty& Other)
		: Type(Other.Type)
		, Level(Other.Level)
		, Exp(Other.Exp)
		, MaxHP(Other.MaxHP)
		, HP(Other.HP)
		, MaxMP(Other.MaxMP)
		, MP(Other.MP)
		, Attack(Other.Attack)
		, Defense(Other.Defense)
	{
	};

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type;

	UPROPERTY(EditDefaultsOnly)
	int Level;

	UPROPERTY(EditDefaultsOnly)
	float Exp;

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

FRoleProperty* getRandomRoleProperty(ERoleType type);

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

	bool InitProperty(FName rowName);
};