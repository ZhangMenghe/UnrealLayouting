// Fill out your copyright notice in the Description page of Project Settings.

#include "cameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AcameraDirector::AcameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcameraDirector::BeginPlay()
{
	Super::BeginPlay();
	fpsCamera = (AActor*)UGameplayStatics::GetPlayerPawn(this,0);
}

// Called every frame
void AcameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

