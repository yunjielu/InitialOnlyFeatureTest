// Fill out your copyright notice in the Description page of Project Settings.


#include "SubActorComponent.h"

#include "UnrealNetwork.h"

// Sets default values for this component's properties
USubActorComponent::USubActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// SetIsReplicated(true);
	// ...
}


// Called when the game starts
void USubActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USubActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USubActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME(USubActorComponent, SubVar1);
	DOREPLIFETIME(USubActorComponent, SubComponentVar1);
 	// DOREPLIFETIME_CONDITION(USubActorComponent, Var2, COND_InitialOnly);
 	DOREPLIFETIME_CONDITION(USubActorComponent, SubComponentVar2, COND_InitialOnly);
}

void USubActorComponent::OnRep_SubComponentVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, SubComponentVar1);
}

void USubActorComponent::OnRep_SubComponentVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, SubComponentVar2);
}


