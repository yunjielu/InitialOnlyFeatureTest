// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponentParent.h"
#include "SubActorComponentB.h"

#include "MyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIALONLYFEATURE_API UMyActorComponent : public UMyActorComponentParent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

	UFUNCTION()
		void OnRep_MyComponentVar1();

	UFUNCTION()
		void OnRep_MyComponentVar2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(ReplicatedUsing = OnRep_MyComponentVar1, BlueprintReadOnly)
		int MyComponentVar1;

	UPROPERTY(ReplicatedUsing = OnRep_MyComponentVar2, BlueprintReadOnly)
		int MyComponentVar2;

	// UPROPERTY(Replicated, Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USubActorComponentB* SubActorComponentB;
};
