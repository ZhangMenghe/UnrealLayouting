// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <fstream>
#include <vector>
#include <string>

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
	const char* filename;
	vector<TCHAR*> BPaddr;
	vector<TSubclassOf<class AActor>> BPSet;
	/*TSubclassOf<class AActor> wallBP;
	TSubclassOf<class AActor> objBP;
	TSubclassOf<class AActor> obstacleBP;
	TSubclassOf<class AActor> pointBP;*/

	void parser_resfile();
	void draw_recommendaton(vector<float> params, vector<float> objInfo);
	void draw_obstacle(vector<float> params);
	void darw_focal_point(vector<float> params);
	void draw_wall(vector<float> params);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void debug_getAllActors();
	void debug_spawn();
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
