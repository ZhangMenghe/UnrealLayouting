#include "tmpFloatingPawn.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Engine.h"
AtmpFloatingPawn::AtmpFloatingPawn()
{

 	// Set this pawn to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;
	RunningTime = 0;
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/floor.floor'"));
	materialToGet = Cast<UMaterialInterface>(Material.Object);
}

/*Built-In Func: Call when game start*/
void AtmpFloatingPawn::BeginPlay()
{
	Super::BeginPlay();

	/*UMaterialInstanceDynamic*DynamicMaterialToUse = UMaterialInstanceDynamic::Create(materialToGet, 0);
	DynamicMaterialToUse->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
	DynamicMaterialToUse->SetVectorParameterValue(FName("Emissive Color"), FLinearColor(1.0f, 0.0f, 0.0f));
	TArray<UStaticMeshComponent*> Components;
	this->GetComponents<UStaticMeshComponent>(Components);
	for (int32 i = 0; i<Components.Num(); i++)
	{
		UStaticMeshComponent* StaticMeshComponent = Components[i];
		StaticMeshComponent->SetMaterial(0, DynamicMaterialToUse);
	}*/
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

