// Fill out your copyright notice in the Description page of Project Settings.

#include "AFPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AAFPSCharacter::AAFPSCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	// create camera component and attach it to capsule
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	//Position the camera(relative to eyes) and allow pawn to control camera rotation
	//FPSCameraComponent->SetRelativeLocation(FVector(.0f,.0f,50.f+BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	//create FPS Mesh
	//FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	FPSMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FPSMesh"));

	//only visible to the PlayerController that has possessed this Character.
	FPSMesh->SetOnlyOwnerSee(true);
	GetMesh()->SetOwnerNoSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	//TopCamMesh->SetStaticMesh()
	static ConstructorHelpers::FClassFinder<AActor> pointBP(TEXT("/Game/Blueprints/thirdPersonBP"));
	cameraPointBP = (UClass *)pointBP.Class;

}

// Called when the game starts or when spawned
void AAFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Using leaves' FPS Character"));
	}
	for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		topCamera = *ActorItr;
		break;
	}
	for (TActorIterator<AlayoutOnScreen> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		layoutScreen = *ActorItr;
		break;
	}
	layoutScreen->parser_resfile();
	//AActor * tmpActor = GetWorld()->SpawnActor<AlayoutOnScreen>(layoutScreenBP, { .0f,.0f,.0f }, { .0f,.0f,.0f });
}

// Called every frame
void AAFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Bind movement axis, BindAxis(axisName, obj, functionName)
	PlayerInputComponent->BindAxis("MoveForwardAndBackward", this, &AAFPSCharacter::FPS_MoveForwardAndBackward);
	PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AAFPSCharacter::FPS_MoveLeftAndRight);

	// Bind Mouse axis, notice functions are defined by Character
	PlayerInputComponent->BindAxis("LookUp", this, &AAFPSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AAFPSCharacter::AddControllerYawInput);

	// Bind Action: action defined in proj setting(actionName, KeyEvent, obj, funName)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAFPSCharacter::FPS_StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAFPSCharacter::FPS_StopJump);

	// Bind pickup Action
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AAFPSCharacter::FPS_PickUp);
	PlayerInputComponent->BindAction("ChangeView", IE_Pressed, this, &AAFPSCharacter::ChangeCameraView);
}

void AAFPSCharacter::FPS_MoveForwardAndBackward(float val){
	if ((Controller != nullptr) && (val != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}

void AAFPSCharacter::FPS_MoveLeftAndRight(float val){
	if ((Controller != nullptr) && (val != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, val);
	}
}

void AAFPSCharacter::FPS_StartJump() {
	bPressedJump = true;

}

void AAFPSCharacter::FPS_StopJump() {
	bPressedJump = false;
}

void AAFPSCharacter::FPS_PickUp() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Trying to pickup something"));
}

void AAFPSCharacter::NotifyActorBeginOverlap(class AActor* otherActor) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("hit!!!"));
}
void AAFPSCharacter::ChangeCameraView() {
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	if (playerController) {
		if (playerController->GetViewTarget() == this) {

			playerController->SetViewTarget(topCamera);

			UWorld * const World = GetWorld();
			if (World) {
				//frotator: y z, x
				AActor * spawnActor = World->SpawnActor<AActor>(cameraPointBP, FPSMesh->GetSocketLocation("FPSMesh"), FRotator(.0f,.0f,.0f));
				spawnActor->AttachToComponent(FPSCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
			
		else
			playerController->SetViewTarget(this);
	}
}