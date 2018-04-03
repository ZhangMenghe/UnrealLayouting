// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Engine/StaticMeshActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "layoutOnScreen.generated.h"

using namespace std;

UCLASS()
class AUTOLAYOUT_API AlayoutOnScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AlayoutOnScreen();

private:
	string filename;
	vector<TCHAR*> BPaddr;
	vector<TSubclassOf<class AActor>> BPSet;
	vector<vector<float>> recParams;
	vector<vector<float>> objectParams;
	vector<AActor *> objects;
	vector<UMaterialInterface*> materialToGetSet;
	//vector<FLinearColor> labelColorSet;
	int currentRecId;
	AStaticMeshActor *floorObj;
	void draw_single_stuff(int cate, vector<float>param, int objId);
	void resize_room(string str, char*delims);
	void parser_resfile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void debug_getAllActors();
	void debug_spawn();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitiallayoutOnScreen();
	void change_recommendation();
};
