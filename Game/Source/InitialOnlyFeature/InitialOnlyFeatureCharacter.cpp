// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#include "InitialOnlyFeatureCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpatialNetDriver.h"

#include "EngineClasses/SpatialNetDriver.h"
#include "Interop/Connection/SpatialWorkerConnection.h"
#include "Interop/SpatialReceiver.h"
#include "CommandRetryHandler.h"

#include "UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// AInitialOnlyFeatureCharacter

AInitialOnlyFeatureCharacter::AInitialOnlyFeatureCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	SubActorComponent = CreateDefaultSubobject<USubActorComponent>(TEXT("SubActorComponent"));
	SubActorComponent->SetIsReplicated(true);

	for (int i = 0; i < MY_ACTOR_COMPONENTS_NUM; ++i)
	{
		// MyActorComponent[i] = CreateDefaultSubobject<UMyActorComponent>(*(FString(TEXT("MyActorComponent_")) + FString::FromInt(i)));
		MyActorComponent.Add(CreateDefaultSubobject<UMyActorComponent>(*(FString(TEXT("MyActorComponent_")) + FString::FromInt(i))));
		MyActorComponent[i]->SetIsReplicated(true);

		// MyActorComponent[i]->SubActorComponent = CreateDefaultSubobject<USubActorComponent>(*(FString(TEXT("MySubActorComponent_")) + FString::FromInt(i)));
		// MyActorComponent[i]->SubActorComponent->SetIsReplicated(true);
	}
}

void AInitialOnlyFeatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInitialOnlyFeatureCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInitialOnlyFeatureCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInitialOnlyFeatureCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AInitialOnlyFeatureCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AInitialOnlyFeatureCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AInitialOnlyFeatureCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AInitialOnlyFeatureCharacter::TouchStopped);

	// yunjie: replication testing code
	PlayerInputComponent->BindAction("Server_IncreaseVar1", IE_Pressed, this, &AInitialOnlyFeatureCharacter::Server_IncreaseVar1);
	PlayerInputComponent->BindAction("Server_IncreaseVar2", IE_Pressed, this, &AInitialOnlyFeatureCharacter::Server_IncreaseVar2);
	PlayerInputComponent->BindAction("Server_IncreaseSubVar", IE_Pressed, this, &AInitialOnlyFeatureCharacter::Server_IncreaseSubVar);
	PlayerInputComponent->BindAction("FetchInitialOnlyData", IE_Pressed, this, &AInitialOnlyFeatureCharacter::FetchInitialOnlyData);
	PlayerInputComponent->BindAction("PrintLocalVar", IE_Pressed, this, &AInitialOnlyFeatureCharacter::PrintLocalVar);


	/*
	PlayerInputComponent->BindAction("Server_IncreaseVar1_Implementation", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_C2S_RPC_OnSingleActor_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_RPC_OnSingleActor_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_RPC_OnSingleActor_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_RPC_OnMultipleActors_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_RPC_OnMultipleActors_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_VariableReplication_OnSingleActor_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_VariableReplication_OnSingleActor_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_VariableReplication_OnSingleActorWithComponent_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_VariableReplication_OnSingleActorWithComponent_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_VariableReplication_OnMultipleActors_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_VariableReplication_OnMultipleActors_Env);
	PlayerInputComponent->BindAction("Initializing_S2C_MulticastRpc_OnSingleActors_Env", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Initializing_S2C_MulticastRpc_OnSingleActors_Env);
	PlayerInputComponent->BindAction("Execute", IE_Pressed, this, &Ayunjie_gdk_testCharacter::Execute);
	*/
}

void AInitialOnlyFeatureCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AInitialOnlyFeatureCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AInitialOnlyFeatureCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AInitialOnlyFeatureCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AInitialOnlyFeatureCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInitialOnlyFeatureCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AInitialOnlyFeatureCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME_CONDITION(Ayunjie_gdk_testCharacter, Var1, COND_OwnerOnly);
	// DOREPLIFETIME_CONDITION(Ayunjie_gdk_testCharacter, Var2, COND_OwnerOnly);

	DOREPLIFETIME(AInitialOnlyFeatureCharacter, ActorVar1);
	DOREPLIFETIME_CONDITION(AInitialOnlyFeatureCharacter, ActorVar2, COND_InitialOnly);
	DOREPLIFETIME(AInitialOnlyFeatureCharacter, SubActorComponent);
	DOREPLIFETIME(AInitialOnlyFeatureCharacter, MyActorComponent);
}


void AInitialOnlyFeatureCharacter::Server_IncreaseVar1_Implementation()
{
	ActorParentVar1++;
	ActorVar1++;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void AInitialOnlyFeatureCharacter::Server_IncreaseVar2_Implementation()
{
	ActorParentVar2++;
	ActorVar2++;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void AInitialOnlyFeatureCharacter::Server_IncreaseSubVar_Implementation()
{
	for (int i = 0; i < MY_ACTOR_COMPONENTS_NUM; ++i)
	{
		MyActorComponent[i]->MyComponentParentVar1++;
		MyActorComponent[i]->MyComponentParentVar2++;

		MyActorComponent[i]->MyComponentVar1++;
		MyActorComponent[i]->MyComponentVar2++;

		MyActorComponent[i]->SubActorComponentB->SubComponentBVar1++;
		MyActorComponent[i]->SubActorComponentB->SubComponentBVar2++;
	}
	
	SubActorComponent->SubComponentVar1++;
	SubActorComponent->SubComponentVar2++;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void AInitialOnlyFeatureCharacter::FetchInitialOnlyData()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - before Var1:%d, Var2: %d"), *FString(__FUNCTION__), ActorVar1, ActorVar2);

	USpatialNetDriver *NetDriver = Cast<USpatialNetDriver>(GetNetDriver());
	Worker_EntityId EntityId = USpatialStatics::GetActorEntityId(this);
	USpatialActorChannel* Channel = NetDriver->GetActorChannelByEntityId(EntityId);
	// Channel->TryFetchInitialOnlyData(EntityId);

	UE_LOG(LogTemp, Warning, TEXT("%s - after Var1:%d, Var2: %d"), *FString(__FUNCTION__), ActorVar1, ActorVar2);
}

void AInitialOnlyFeatureCharacter::OnRep_ActorVar1()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - %d"), *FString(__FUNCTION__), ActorVar1);
	// UE_LOG(LogTemp, Warning, TEXT("%s - %d", *FString(__FUNCTION__), Var1);
}

void AInitialOnlyFeatureCharacter::OnRep_ActorVar2()
{
	UE_LOG(LogTemp, Warning, TEXT("%s - %d"), *FString(__FUNCTION__), ActorVar2);
}


void AInitialOnlyFeatureCharacter::PrintLocalVar()
{
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - ActorParentVar1:%d, ActorParentVar2:%d"), *FString(__FUNCTION__), this, ActorParentVar1, ActorParentVar2);
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - ActorVar1:%d, ActorVar2:%d"), *FString(__FUNCTION__), this, ActorVar1, ActorVar2);

	for (int i = 0; i < MY_ACTOR_COMPONENTS_NUM; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s(%p) - MyComponentParentVar1:%d, MyComponentParentVar2:%d"), *FString(__FUNCTION__), MyActorComponent[i], MyActorComponent[i]->MyComponentParentVar1, MyActorComponent[i]->MyComponentParentVar2);
		UE_LOG(LogTemp, Warning, TEXT("%s(%p) - MyComponentVar1:%d, MyComponentVar2:%d"), *FString(__FUNCTION__), MyActorComponent[i], MyActorComponent[i]->MyComponentVar1, MyActorComponent[i]->MyComponentVar2);
		UE_LOG(LogTemp, Warning, TEXT("%s(%p) - MySubComponentVar1:%d, MySubComponentVar2:%d"), *FString(__FUNCTION__), MyActorComponent[i]->SubActorComponentB, MyActorComponent[i]->SubActorComponentB->SubComponentBVar1, MyActorComponent[i]->SubActorComponentB->SubComponentBVar2);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s(%p) - SubComponentVar1:%d, SubComponentVar2:%d"), *FString(__FUNCTION__), SubActorComponent, SubActorComponent->SubComponentVar1, SubActorComponent->SubComponentVar2);
}
