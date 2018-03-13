// Fill out your copyright notice in the Description page of Project Settings.

#include "layoutOnScreen.h"
#include "EngineUtils.h"
#include "Engine.h"
// Sets default values
AlayoutOnScreen::AlayoutOnScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	filename = "/Game/InputData/intermediate/recommendation.txt";
	BPaddr.push_back(TEXT("/Game/Blueprints/wallBP"));
	BPaddr.push_back(TEXT("/Game/Blueprints/objBP"));
	BPaddr.push_back(TEXT("/Game/Blueprints/obstacleBP"));
	BPaddr.push_back(TEXT("/Game/Blueprints/focalBP"));
	for (int i = 0; i < 4; i++) {
		static ConstructorHelpers::FClassFinder<AActor> findBP(BPaddr[i]);
		if (findBP.Class) {
			TSubclassOf<class AActor> tmpBP = (UClass *)findBP.Class;
			BPSet.push_back(tmpBP);
		}
	}
	/*static ConstructorHelpers::FClassFinder<AActor> findBP(TEXT("/Game/Blueprints/pikachu"));
	if (findBP.Class) {
		TSubclassOf<class AActor> tmpBP = (UClass *)findBP.Class;
		BPSet.push_back(tmpBP);
	}*/

}

// Called when the game starts or when spawned
void AlayoutOnScreen::BeginPlay()
{
	Super::BeginPlay();


	debug_spawn();
}

// Called every frame
void AlayoutOnScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AlayoutOnScreen::debug_getAllActors() {
	//While not reached end (overloaded bool operator)
	for (FActorIterator AllActorsItr = FActorIterator(GetWorld()); AllActorsItr; ++AllActorsItr) {
		if (AllActorsItr->GetClass()->GetDesc() == "autoLayoutGenerator") {
			//GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Yellow, TEXT("found tmpOpencv"));
			break;
		}
	}
}
void AlayoutOnScreen::debug_spawn() {
	UWorld * const World = GetWorld();
	if (World) {
		AActor * wall = World->SpawnActor<AActor>(BPSet[0], FVector(0,3000,250), FRotator(.0f,.0f,.0f));
		TArray<UActorComponent *> components;
		wall->GetComponents(components);
		for (int32 i = 0; i < components.Num(); ++i) {
			USceneComponent* sc = Cast<USceneComponent>(components[i]);
			if (sc)
				sc->SetWorldScale3D(FVector(80, 1, 5));
		}
	}
}
void AlayoutOnScreen::draw_wall(vector<float> params) {

}
void AlayoutOnScreen::darw_focal_point(vector<float> params) {

}
void AlayoutOnScreen::draw_obstacle(vector<float> params) {

}
void AlayoutOnScreen::draw_recommendaton(vector<float> params, vector<float> objInfo) {

}

void AlayoutOnScreen::parser_resfile() {
	ifstream instream(filename);
	string str;
	vector<vector<float>> parameters;
	char  delims[] = " :,\t\n|[]";
	char* context = nullptr;
	int state = -1;
	vector<float> currentObj;
	while (instream && getline(instream, str)) {
		if (!str.length())
			continue;
		char * charline = new char[300];
		int r = strcpy_s(charline, 300, str.c_str());
		vector<float>param;
		char * token = strtok_s(charline, delims, &context);
		switch (token[0])
		{
		case 'W'://wall
			state = 0;
			break;
		case 'F'://furniture
			state = 1;
			break;
		case 'P'://focal point
			state = 2;
			break;
		case 'O'://obstacle
			state = 3;
			break;
		case 'R'://Recommendation for an object
			state = 4;
			break;
		default:
			while (token != nullptr) {
				param.push_back(atof(token));
				token = strtok_s(nullptr, delims, &context);
			}
			switch (state)
			{
			case 0:
				draw_wall(param);
				break;
			case 1:
				currentObj = param;
				break;
			case 2:
				darw_focal_point(param);
				break;
			case 3:
				draw_obstacle(param);
				break;
			case 4:
				draw_recommendaton(param, currentObj);
				break;
			default:
				break;
			}
			break;
		}
	}
	instream.close();
}