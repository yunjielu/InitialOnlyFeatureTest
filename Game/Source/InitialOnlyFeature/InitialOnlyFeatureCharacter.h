// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SubActorComponent.h"
#include "MyActorComponent.h"
#include "CharacterParent.h"
#include "InitialOnlyFeatureCharacter.generated.h"

#define MY_ACTOR_COMPONENTS_NUM		1

UCLASS(config=Game, SpatialType)
class AInitialOnlyFeatureCharacter : public ACharacterParent
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AInitialOnlyFeatureCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


protected:
	UFUNCTION(Server, Reliable)
		void Server_IncreaseVar1();

	UFUNCTION(Server, Reliable)
		void Server_IncreaseVar2();

	UFUNCTION(Server, Reliable)
		void Server_IncreaseSubVar();

	void FetchInitialOnlyData();

	void PrintLocalVar();

	UFUNCTION()
		void OnRep_ActorVar1();
	UFUNCTION()
		void OnRep_ActorVar2();

	UPROPERTY(ReplicatedUsing = OnRep_ActorVar1, BlueprintReadOnly)
		int32 ActorVar1;
	UPROPERTY(ReplicatedUsing = OnRep_ActorVar2, BlueprintReadOnly)
		int32 ActorVar2;

	UPROPERTY(Replicated, Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		USubActorComponent* SubActorComponent;

	UPROPERTY(Replicated, Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		TArray<UMyActorComponent*>				MyActorComponent;
		// UMyActorComponent* MyActorComponent[MY_ACTOR_COMPONENTS_NUM];
};

