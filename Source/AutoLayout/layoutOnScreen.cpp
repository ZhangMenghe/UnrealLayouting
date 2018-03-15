// Fill out your copyright notice in the Description page of Project Settings.

#include "layoutOnScreen.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
float dist_of_points(float x1, float y1, float x2, float y2) {
	return sqrtf(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// Sets default values
AlayoutOnScreen::AlayoutOnScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FString dir = FPaths::GameDir() + FString("InputData/intermediate/recommendation.txt");
	filename = string(TCHAR_TO_UTF8(*dir));

	//filename = "E:/recommendation.txt";
	currentRecId = -1;

	static ConstructorHelpers::FClassFinder<AActor> wallBP(TEXT("/Game/Blueprints/wallBP"));
	BPSet.push_back((UClass *)wallBP.Class);

	static ConstructorHelpers::FClassFinder<AActor> objBP(TEXT("/Game/Blueprints/objBP"));
	BPSet.push_back((UClass *)objBP.Class);

	static ConstructorHelpers::FClassFinder<AActor> focalBP(TEXT("/Game/Blueprints/focalBP"));
	BPSet.push_back((UClass *)focalBP.Class);

	static ConstructorHelpers::FClassFinder<AActor> obsBP(TEXT("/Game/Blueprints/obstacleBP"));
	BPSet.push_back((UClass *)obsBP.Class);

	char* names[9] = { "Material'/Game/Material/chair.chair'" ,"Material'/Game/Material/coffetable.coffetable'" ,"Material'/Game/Material/sofa.sofa'" 
		"Material'/Game/Material/endtable.endtable'" ,"Material'/Game/Material/bed.bed'" ,"Material'/Game/Material/nightstand.nightstand'" ,
		"Material'/Game/Material/shelf.shelf'" ,"Material'/Game/Material/table.table'" ,"Material'/Game/Material/others.others'" };
	for (int i = 0; i < 9; i++) {
		static ConstructorHelpers::FObjectFinder<UMaterial> Material(*FString(names[i]));
		materialToGetSet.push_back(Cast<UMaterialInterface>(Material.Object));
	}
}

// Called when the game starts or when spawned
void AlayoutOnScreen::BeginPlay()
{
	Super::BeginPlay();
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
void AlayoutOnScreen::draw_single_stuff(int cate, vector<float>param, int ObjId = -1) {
	float cx=0, cy=0, cz=0;
	float sx = 10, sy = 10, sz = 30;
	float rot = 0;
	switch (cate)
	{
	case 0:
		cx = (param[2] + param[4]) / 2;
		cy = (param[3] + param[5]) / 2;
		rot = param[6];
		sx = dist_of_points(param[2], param[3], param[4], param[5]);
		sz = 100;
		break;
	case 1:
		sx = objectParams[ObjId][3]; sy = objectParams[ObjId][4]; sz = objectParams[ObjId][2];
		cx = param[1]; cy = param[2];
		rot = param[3];
		if (objects.size() > ObjId) {
			objects[ObjId]->SetActorLocationAndRotation(FVector(cx*10, cy*10, sz*5), FRotator(.0f, rot / PI * 180, .0f).Quaternion());
			return;
		}
		break;
	case 2:
		cx = param[1];
		cy = param[2];
		sx = sy = sz = 50;
		break;
	case 3:
		cx = (param[0] + param[4]) / 2;
		cy = (param[1] + param[5]) / 2;
		rot = atanf((param[7] - param[3]) / (param[6] - param[2])) * 180 / 3.14;
		sx = dist_of_points(param[0], param[1], param[2], param[3]);
		sy = dist_of_points(param[2], param[3], param[4], param[5]);
		break;
	default:
		break;
	}
	sx /= 10; sy /= 10; sz /= 10;
	cx *= 10; cy *= 10; cz = sz * 50;
	rot = rot / PI * 180;

	UWorld * const World = GetWorld();
	if (World) {
		//frotator: y z, x
		AActor * spawnActor = World->SpawnActor<AActor>(BPSet[cate], FVector(cx, cy, cz), FRotator(.0f, rot, .0f));
		TArray<UActorComponent *> components;
		spawnActor->GetComponents(components);
		for (int32 i = 0; i < components.Num(); ++i) {
			USceneComponent* sc = Cast<USceneComponent>(components[i]);
			sc->SetWorldScale3D(FVector(sx, sy, sz));
		}
		if (cate == 1) {
			UMaterialInstanceDynamic*DynamicMaterialToUse = UMaterialInstanceDynamic::Create(materialToGetSet[int(objectParams[ObjId][1])], 0);
			//DynamicMaterialToUse->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
			//DynamicMaterialToUse->SetVectorParameterValue(FName("Emissive Color"),FLinearColor(1.0f, 0.0f, 0.0f));
			TArray<UStaticMeshComponent*> Components;
			spawnActor->GetComponents<UStaticMeshComponent>(Components);
			for (int32 i = 0; i<Components.Num(); i++)
			{
				UStaticMeshComponent* StaticMeshComponent = Components[i];
				StaticMeshComponent->SetMaterial(0, DynamicMaterialToUse);
			}

			objects.push_back(spawnActor);
		}
			
			
	}
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
			state = 4;
			break;
		case 'P'://focal point
			state = 2;
			break;
		case 'O'://obstacle
			state = 3;
			break;
		case 'R'://furniture pos recommendation
			state = 1;
			
		default:
			while (token != nullptr) {
				param.push_back(atof(token));
				token = strtok_s(nullptr, delims, &context);
			}
			if (state == 1)
				recParams.push_back(param);
			else if (state == 4)
				objectParams.push_back(param);
			else
				draw_single_stuff(state, param);
			break;
		}
	}
	instream.close();
	// test to draw single recommendation
	//draw_single_stuff(1, recParams[2], 0);
}
void AlayoutOnScreen::change_recommendation() {
	currentRecId = (currentRecId + 1) % 3;
	for (int i = 0; i < objectParams.size(); i++) {
		draw_single_stuff(1, recParams[3 * i + currentRecId], i);
	}
		
}