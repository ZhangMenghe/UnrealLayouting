#pragma once

#include "automatedLayout.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "autoLayoutGenerator.generated.h"

UCLASS()
class AUTOLAYOUT_API AautoLayoutGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AautoLayoutGenerator();

	char* inputObjFileName;
	Room * room;
	vector<float> weights;
	Size2f roomSize;
	void parser_inputfile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
