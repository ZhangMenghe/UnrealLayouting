// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoLayoutGameModeBase.h"
#include "Engine.h"
AAutoLayoutGameModeBase::AAutoLayoutGameModeBase(const class FObjectInitializer & ObjectInitializer)
	:Super(ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/pikachu"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}



