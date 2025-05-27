// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RoleAnimInstance.generated.h"

class UAnimSequence;
class UAnimMontage;

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

	void SetState(ERoleAnimState State);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr< UAnimSequence > IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr< UAnimSequence > WalkAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr< UAnimSequence > RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	class UAnimMontage*  CurAnimMontage;

	UPROPERTY(BlueprintReadOnly)
	ERoleAnimState RoleAnimState = ERoleAnimState::IDLE;
};
