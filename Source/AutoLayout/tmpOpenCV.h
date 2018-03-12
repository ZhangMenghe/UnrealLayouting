// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tmpOpenCV.generated.h"

UCLASS()
class AUTOLAYOUT_API AtmpOpenCV : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtmpOpenCV();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
