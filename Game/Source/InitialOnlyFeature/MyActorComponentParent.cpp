// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponentParent.h"

#include "UnrealNetwork.h"

// Sets default values for this component's properties
UMyActorComponentParent::UMyActorComponentParent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UMyActorComponentParent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponentParent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMyActorComponentParent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyActorComponentParent, MyComponentParentVar1);
	DOREPLIFETIME_CONDITION(UMyActorComponentParent, MyComponentParentVar2, COND_InitialOnly);
}

void UMyActorComponentParent::OnRep_MyComponentParentVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, MyComponentParentVar1);
}

void UMyActorComponentParent::OnRep_MyComponentParentVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, MyComponentParentVar2);
}


