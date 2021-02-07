// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SubActorComponentB.h"

#include "MyActorComponentParent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIALONLYFEATURE_API UMyActorComponentParent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponentParent();

	UFUNCTION()
		void OnRep_MyComponentParentVar1();

	UFUNCTION()
		void OnRep_MyComponentParentVar2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_MyComponentParentVar1, BlueprintReadOnly)
		int MyComponentParentVar1;

	UPROPERTY(ReplicatedUsing = OnRep_MyComponentParentVar2, BlueprintReadOnly)
		int MyComponentParentVar2;
};
