// Fill out your copyright notice in the Description page of Project Settings.

#include "heightMapGenerator.h"
#include "Engine.h"
#include <string>

using namespace cv;
using namespace std;
// Sets default values
AheightMapGenerator::AheightMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FString dir = FPaths::GameDir() + FString("InputData/intermediate/heightMapData.yml");
	heightMap_filepath = string(TCHAR_TO_UTF8(*dir));
	FileStorage fs;
	fs.open(heightMap_filepath, FileStorage::READ);
	heightMap = fs["floatdata"].mat();
}

// Called when the game starts or when spawned
void AheightMapGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AheightMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

