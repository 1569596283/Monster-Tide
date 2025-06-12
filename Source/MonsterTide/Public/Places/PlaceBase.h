// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class MONSTERTIDE_API APlaceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	// ��д������������
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	// ������������
	virtual void NotifyActorOnInputTouchEnd(ETouchIndex::Type FingerIndex) override;

	// ��ѡ����ͣ�¼�
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
