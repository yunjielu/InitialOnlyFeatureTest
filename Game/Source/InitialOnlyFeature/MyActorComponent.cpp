// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

#include "UnrealNetwork.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SubActorComponentB = CreateDefaultSubobject<USubActorComponentB>(TEXT("MySubActorComponentB"));
	SubActorComponentB->SetIsReplicated(true);
	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMyActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyActorComponent, MyComponentVar1);
	DOREPLIFETIME_CONDITION(UMyActorComponent, MyComponentVar2, COND_InitialOnly);
	// DOREPLIFETIME(UMyActorComponent, SubActorComponentB);
}

void UMyActorComponent::OnRep_MyComponentVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, MyComponentVar1);
}

void UMyActorComponent::OnRep_MyComponentVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - %d"), *FString(__FUNCTION__), this, MyComponentVar2);
}


