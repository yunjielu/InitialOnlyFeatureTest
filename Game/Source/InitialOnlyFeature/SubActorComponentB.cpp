// Fill out your copyright notice in the Description page of Project Settings.


#include "SubActorComponentB.h"

#include "UnrealNetwork.h"

// Sets default values for this component's properties
USubActorComponentB::USubActorComponentB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// SetIsReplicated(true);
	// ...
}


// Called when the game starts
void USubActorComponentB::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USubActorComponentB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USubActorComponentB::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME(USubActorComponentB, SubVar1);
	DOREPLIFETIME(USubActorComponentB, SubComponentBVar1);
 	// DOREPLIFETIME_CONDITION(USubActorComponentB, Var2, COND_InitialOnly);
 	DOREPLIFETIME_CONDITION(USubActorComponentB, SubComponentBVar2, COND_InitialOnly);
}

void USubActorComponentB::OnRep_SubComponentBVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, SubComponentBVar1);
}

void USubActorComponentB::OnRep_SubComponentBVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, SubComponentBVar2);
}


