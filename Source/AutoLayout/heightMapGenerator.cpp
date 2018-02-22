// Fill out your copyright notice in the Description page of Project Settings.

#include "heightMapGenerator.h"
#include <fstream>
using namespace std;

// Sets default values
AheightMapGenerator::AheightMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
void AheightMapGenerator::parser_heightDataFile(const char*filename, Mat_<float>& heightMap) {
	ifstream instream(filename);
	string str;
	vector<vector<float>> contents;
	char  delims[] = " :,\t\n";
	char * context = nullptr;
	while (instream && getline(instream, str)) {
		if (!str.length())
			continue;
		int len = str.length();
		char * charline = new char[len];
		int r = strcpy_s(charline, len, str.c_str());
		vector<float> row;
		char * token = strtok_s(charline, delims, &context);
		while (token != nullptr) {
			row.push_back(atof(token));
			token = strtok_s(nullptr, delims, &context);
		}
		contents.push_back(row);
	}
	instream.close();
	heightMap = Mat(contents);	
}

