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

	// 重写函数来处理点击
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	// 新增触摸处理
	virtual void NotifyActorOnInputTouchEnd(ETouchIndex::Type FingerIndex) override;

	// 可选：悬停事件
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
