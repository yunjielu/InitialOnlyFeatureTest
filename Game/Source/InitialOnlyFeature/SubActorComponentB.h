// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SubActorComponentB.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USubActorComponentB : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USubActorComponentB();

	UFUNCTION()
		void OnRep_SubComponentBVar1();

	UFUNCTION()
		void OnRep_SubComponentBVar2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_SubComponentBVar1, BlueprintReadOnly)
		int SubComponentBVar1;

	UPROPERTY(ReplicatedUsing = OnRep_SubComponentBVar2, BlueprintReadOnly)
		int SubComponentBVar2;
};
