// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RoleAnimInstance.generated.h"

class UAnimSequence;
class UAnimMontage;
class UBlendSpace;

UENUM(BlueprintType)
enum class ERoleAnimState :uint8 {
	IDLE,
	REST
};

/**
 *
 */
UCLASS()
class MONSTERTIDE_API URoleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	float PlayAttackAnimation();
	float PlayDeadAnimation();

	void SetState(ERoleAnimState State);

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float Speed = 0.f;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeadMontage;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	class UAnimMontage*  CurAnimMontage;

	UPROPERTY(BlueprintReadOnly)
	ERoleAnimState RoleAnimState = ERoleAnimState::IDLE;
};
