// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoleBase.generated.h"

class URolePropertyComponent;
struct FRoleProperty;

UCLASS()
class MONSTERTIDE_API ARoleBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARoleBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitRole(FRoleProperty* RoleProperty);

	void RemoveRole();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<URolePropertyComponent> RolePropertyComponent;

};
