#pragma once

#include "automatedLayout.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "autoLayoutGenerator.generated.h"

//#define DEFAULT_INPUT_PARAMETER_FILE "E:/layoutParam.txt"
//#define DEFAULT_ROOM_SIZE Size2f(800.f, 600.f)

UCLASS()
class AUTOLAYOUT_API AautoLayoutGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AautoLayoutGenerator();

	string inputObjFileName;
	string outputFileName;
	Room * room;
	vector<float> weights;
	Size2f roomSize;
	void parser_inputfile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
