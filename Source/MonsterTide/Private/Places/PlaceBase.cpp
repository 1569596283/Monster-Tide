// Fill out your copyright notice in the Description page of Project Settings.


#include "Places/PlaceBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlaceBase::APlaceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlaceBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlaceBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyActorOnClicked"));
}

void APlaceBase::NotifyActorBeginCursorOver()
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyActorBeginCursorOver"));
}

void APlaceBase::NotifyActorEndCursorOver()
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyActorEndCursorOver"));
}

// Called every frame
void APlaceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

