// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SubActorComponent.h"
#include "MyActorComponent.h"
#include "CharacterParent.generated.h"

#define MY_ACTOR_COMPONENTS_NUM		1

UCLASS(config=Game, SpatialType)
class ACharacterParent : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterParent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
		void OnRep_ActorParentVar1();
	UFUNCTION()
		void OnRep_ActorParentVar2();

	UPROPERTY(ReplicatedUsing = OnRep_ActorParentVar1, BlueprintReadOnly)
		int32 ActorParentVar1;
	UPROPERTY(ReplicatedUsing = OnRep_ActorParentVar2, BlueprintReadOnly)
		int32 ActorParentVar2;
};

