// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SubActorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USubActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USubActorComponent();

	UFUNCTION()
		void OnRep_SubComponentVar1();

	UFUNCTION()
		void OnRep_SubComponentVar2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_SubComponentVar1, BlueprintReadOnly)
		int SubComponentVar1;

	UPROPERTY(ReplicatedUsing = OnRep_SubComponentVar2, BlueprintReadOnly)
		int SubComponentVar2;
};
