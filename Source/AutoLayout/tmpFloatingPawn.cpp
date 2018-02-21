#include "tmpFloatingPawn.h"
AtmpFloatingPawn::AtmpFloatingPawn()
{

 	// Set this pawn to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;
	RunningTime = 0;
}

/*Built-In Func: Call when game start*/
void AtmpFloatingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtmpFloatingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector is (x,y,z) in 3d
	FVector newLocation = GetActorLocation();
	float DelataHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	newLocation.Z += DelataHeight * 20.f;
	RunningTime += DeltaTime;
	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void AtmpFloatingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

