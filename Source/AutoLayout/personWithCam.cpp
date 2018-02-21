// Fill out your copyright notice in the Description page of Project Settings.

#include "personWithCam.h"


// Sets default values
ApersonWithCam::ApersonWithCam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ApersonWithCam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ApersonWithCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ApersonWithCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

