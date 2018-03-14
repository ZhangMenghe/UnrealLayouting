// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "layoutOnScreen.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "AFPSCharacter.generated.h"

UCLASS()
class AUTOLAYOUT_API AAFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TSubclassOf<class AActor> cameraPointBP;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//simulate collider
	virtual void NotifyActorBeginOverlap(AActor* Other) override;
	
	// Handle Movement
	UFUNCTION()
		void FPS_MoveForwardAndBackward(float val);
	UFUNCTION()
		void FPS_MoveLeftAndRight(float val);
	// Handle Actions
	UFUNCTION()
		void FPS_StartJump();
	UFUNCTION()
		void FPS_StopJump();
	UFUNCTION()
		void FPS_PickUp();
	UFUNCTION()
		void ChangeCameraView();
	UPROPERTY(EditAnywhere)
		AActor* topCamera;
	// FPS Camera: use to adjust camera properties
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// PFS-view mesh, visible only default
	//USkeletalMeshComponent: an instance of an animated SkeletalMesh asset.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		//USkeletalMeshComponent * FPSMesh;
		UStaticMeshComponent * FPSMesh;
	UPROPERTY()
		UPrimitiveComponent* colliderTrigger;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AlayoutOnScreen> layoutScreenClass;
	AlayoutOnScreen* layoutScreen;
};
