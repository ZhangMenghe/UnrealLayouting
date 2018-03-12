// Fill out your copyright notice in the Description page of Project Settings.

#include "tmpOpenCV.h"
#include <vector>
#include "Engine.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)
using namespace std;
using namespace cv;

// Sets default values
AtmpOpenCV::AtmpOpenCV()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AtmpOpenCV::BeginPlay()
{
	Super::BeginPlay();
	Mat dst = Mat::zeros(100, 100, CV_8UC1);
	vector<vector<Point> > contours;
	vector<Point> contour;
	contour.push_back(Point(0, 0));
	contour.push_back(Point(0, 20));
	contour.push_back(Point(20, 20));
	contour.push_back(Point(20, 0));
	contours.push_back(contour);
	drawContours(dst, contours, -1, 1, FILLED, 8);
	string tmp = "get contour area:" + to_string(cv::sum(dst)[0]);
	print(tmp.c_str());
	//cout << cv::sum(dst) << endl;
}

// Called every frame
void AtmpOpenCV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

