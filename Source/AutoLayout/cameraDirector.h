// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cameraDirector.generated.h"

UCLASS()
class AUTOLAYOUT_API AcameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
		AActor* fpsCamera;
	UPROPERTY(EditAnywhere)
		AActor* topCamera;
	float TimeToNextCameraChange;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
