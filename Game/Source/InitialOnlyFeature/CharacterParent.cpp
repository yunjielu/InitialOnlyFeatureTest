// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#include "CharacterParent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpatialNetDriver.h"

#include "EngineClasses/SpatialNetDriver.h"
#include "Interop/Connection/SpatialWorkerConnection.h"
#include "Interop/SpatialReceiver.h"
#include "CommandRetryHandler.h"

#include "UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// ACharacterParent

ACharacterParent::ACharacterParent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACharacterParent::BeginPlay()
{
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACharacterParent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
}

void ACharacterParent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterParent, ActorParentVar1);
	DOREPLIFETIME_CONDITION(ACharacterParent, ActorParentVar2, COND_InitialOnly);
}

void ACharacterParent::OnRep_ActorParentVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - %d"), *FString(__FUNCTION__), ActorParentVar1);
	// UE_LOG(LogTemp, Warning, TEXT("%s - %d", *FString(__FUNCTION__), Var1);
}

void ACharacterParent::OnRep_ActorParentVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - %d"), *FString(__FUNCTION__), ActorParentVar2);
}


