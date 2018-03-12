// Fill out your copyright notice in the Description page of Project Settings.

#include "autoLayoutGenerator.h"
#include "processFixedObjects.h"
//using namespace fixedOjects;

// Sets default values
AautoLayoutGenerator::AautoLayoutGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	inputObjFileName = new char[100];
	int r = strcpy_s(inputObjFileName, 100, "E:/layoutParam.txt");

	roomSize = Size2f(800.f, 600.f);
	room = new Room(roomSize.width, roomSize.height);
	
}

// Called when the game starts or when spawned
void AautoLayoutGenerator::BeginPlay()
{
	Super::BeginPlay();
	parser_inputfile();
	if (room != nullptr && (room->objctNum != 0 || room->wallNum != 0)) {
		automatedLayout* layout = new automatedLayout(room, weights);
		layout->generate_suggestions();
		layout->display_suggestions();
	}
}

// Called every frame
void AautoLayoutGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AautoLayoutGenerator::parser_inputfile() {
	ifstream instream(inputObjFileName);
	string str;
	vector<vector<float>> parameters;
	vector<char> cateType;
	char  delims[] = " :,\t\n";
	char* context = nullptr;
	while (instream && getline(instream, str)) {
		if (!str.length())
			continue;
		char * charline = new char[300];
		int r = strcpy_s(charline, 300, str.c_str());
		char * itemCate = strtok_s(charline, delims, &context);
		vector<float>param;
		char * token = strtok_s(nullptr, delims, &context);
		while (token != nullptr) {
			param.push_back(atof(token));
			token = strtok_s(nullptr, delims, &context);
		}
		parameters.push_back(param);
		cateType.push_back(itemCate[0]);
	}

	instream.close();
	int itemNum = cateType.size();
	vector<vector<float>> fixedObjParams;
	vector<vector<float>> mergedObjParams;
	int groupid;
	vector<int> groupedIds;
	for (int i = 0; i < itemNum; i++) {
		switch (cateType[i])
		{
		case '#':
			break;
			//add a new wall
		case 'w':
			room->add_a_wall(Vec3f(parameters[i][0], parameters[i][1], parameters[i][2]), parameters[i][3], parameters[i][4], parameters[i][5]);
			break;
		case 'f':
			//groupid = parameters[i].size() == 8 ? 0 : parameters[i][8];
			room->add_an_object(parameters[i], 0);
			break;
		case 'p':
			groupid = parameters[i].size() == 3 ? 0 : parameters[i][3];
			room->add_a_focal_point(Vec3f(parameters[i][0], parameters[i][1], parameters[i][2]), groupid);
			break;
		case 'o':
			fixedObjParams.push_back(parameters[i]);
			break;
		case 'g':
			mergedObjParams.push_back(mergeAgroup(fixedObjParams, parameters[i]));
			for (int k = 0; k < parameters[i].size(); k++)
				groupedIds.push_back(parameters[i][k]);
			break;
		case 'v':
			for (int n = 0; n < parameters[i].size(); n++)
				weights.push_back(parameters[i][n]);
			break;
		default:
			break;
		}
	}
	//UNCOMMENT those debug parts to draw un-groupped items
	if (mergedObjParams.size() != 0) {
		//vector<vector<Point2f>>debug_vector;
		for (int i = 0; i < mergedObjParams.size(); i++)
			room->add_an_obstacle(mergedObjParams[i]);
		//room->add_an_object(mergedObjParams[i]);
		//uncomment this to make those merged object as free objects
		sort(groupedIds.begin(), groupedIds.end());
		for (int compareIdx = fixedObjParams.size() - 1, gidx = groupedIds.size() - 1; compareIdx > -1; ) {
			if (compareIdx > groupedIds[gidx]) {
				//vector<Point2f> rect1;
				//for (int i = 0; i < 4; i++)
				//	rect1.push_back(Point2f(fixedObjParams[compareIdx][2 * i], fixedObjParams[compareIdx][2 * i + 1]));
				//debug_vector.push_back(rect1);
				room->add_an_object(fixedObjParams[compareIdx]);
				compareIdx--;
			}
			else if (compareIdx == groupedIds[gidx]) {
				compareIdx--; gidx--;
			}
			else
				gidx--;
		}
		//write_out_file(debug_vector);
	}
	else {
		for (int i = 0; i < fixedObjParams.size(); i++)
			room->add_an_object(fixedObjParams[i]);
	}


	if (weights.size() < 11) {
		for (int i = weights.size(); i < 11; i++)
			weights.push_back(1.0f);
	}
}