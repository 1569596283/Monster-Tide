// Fill out your copyright notice in the Description page of Project Settings.


#include "Places/PlaceBase.h"
#include "Components/StaticMeshComponent.h"
#include "Roles/HeroManager.h"

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
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->CreateHeroAtLocation(GetActorLocation());
}

void APlaceBase::NotifyActorBeginCursorOver()
{
}

void APlaceBase::NotifyActorEndCursorOver()
{
}

// Called every frame
void APlaceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

