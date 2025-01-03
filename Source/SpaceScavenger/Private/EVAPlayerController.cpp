// Fill out your copyright notice in the Description page of Project Settings.
#include "EVAPlayerController.h"
#include "Interactable.h"
#include "EasingFunctions.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerHandItem.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MathUtil.h"
#include "SpaceScavenger/EvaDesignData.h"


// Sets default values
AEVAPlayerController::AEVAPlayerController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEVAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EvaDesignData = EvaDesignData.LoadSynchronous();
	MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = EvaDesignData->WalkSpeed;
	MovementComponent->MaxWalkSpeedCrouched = EvaDesignData->CrouchWalkSpeed;
	MovementComponent->AirControl = EvaDesignData->AirControl;
	MovementComponent->NavAgentProps.bCanCrouch = true;
	BodyCapsuleComponent = GetCapsuleComponent(); 
	DefaultCapsuleHalfHeight = BodyCapsuleComponent->GetUnscaledCapsuleHalfHeight();

	
	RecalculateCrouchedEyeHeight();
}

// Called every frame
void AEVAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetermineHover();


	const bool IsGravityNull = !BodyCapsuleComponent->IsGravityEnabled();
	if (IsGravityNull != (CurrentMovementType == EMovementType::VE_EVA))
		ToggleEva();

	
	if (MovementComponent->IsCrouching())
		CrouchNorm = FMathf::Clamp(CrouchNorm - (EvaDesignData->CrouchSpeed * DeltaTime), 0, 1);
	else		
		CrouchNorm = FMathf::Clamp(CrouchNorm + (EvaDesignData->CrouchSpeed * DeltaTime), 0, 1);
	
	BodyCapsuleComponent->SetCapsuleHalfHeight(FMath::Lerp(CrouchedEyeHeight,DefaultCapsuleHalfHeight, UEasingFunctions::EaseInOutExpo(CrouchNorm)));
}

// Called to bind functionality to input
void AEVAPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	const APlayerController* Player = GetWorld()->GetFirstPlayerController();
	if (Input)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}
		
		Input->BindAction(LookAction, ETriggerEvent::Triggered,this, &AEVAPlayerController::Look);
		Input->BindAction(LookAction, ETriggerEvent::Completed,this, &AEVAPlayerController::Look);
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AEVAPlayerController::Interact);
		ConfigureRegularMovement();
	}
}

void AEVAPlayerController::ConfigureEvaMovement()
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	// Log
	UE_LOG(LogTemp, Warning, TEXT("Configuring Eva Movement") );
	for(FEnhancedInputActionEventBinding* Action : DynamicMovementBindings)
	{
		Input->RemoveBinding(*Action);
	}
	DynamicMovementBindings.Empty();
	
	FEnhancedInputActionEventBinding& movementTriggered = Input->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AEVAPlayerController::MoveEva);
	FEnhancedInputActionEventBinding& movementCompleted = Input->BindAction(MoveAction, ETriggerEvent::Completed,this, &AEVAPlayerController::MoveEva);
	FEnhancedInputActionEventBinding& jumpTriggered = Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEVAPlayerController::JumpHandlerEva);
	FEnhancedInputActionEventBinding& crouchTriggered = Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEVAPlayerController::CrouchEva);
	FEnhancedInputActionEventBinding& crouchCompleted = Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEVAPlayerController::CrouchEva);	

	DynamicMovementBindings.Emplace(&movementTriggered);
	DynamicMovementBindings.Emplace(&movementCompleted);
	DynamicMovementBindings.Emplace(&jumpTriggered);
	DynamicMovementBindings.Emplace(&crouchTriggered);
	DynamicMovementBindings.Emplace(&crouchCompleted);


	
}

void AEVAPlayerController::ConfigureRegularMovement()
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	UE_LOG(LogTemp, Warning, TEXT("Configuring Regular Movement") );
	for(FEnhancedInputActionEventBinding* Action : DynamicMovementBindings)
	{
		Input->RemoveBinding(*Action);
	}
	DynamicMovementBindings.Empty();
	
	FEnhancedInputActionEventBinding& movementTriggered = Input->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AEVAPlayerController::Move);
	FEnhancedInputActionEventBinding& movementCompleted = Input->BindAction(MoveAction, ETriggerEvent::Completed,this, &AEVAPlayerController::Move);
	FEnhancedInputActionEventBinding& jumpTriggered = Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEVAPlayerController::Jump);
	FEnhancedInputActionEventBinding& crouchTriggered = Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEVAPlayerController::Crouch);
	FEnhancedInputActionEventBinding& crouchCompleted = Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEVAPlayerController::Crouch);	


	DynamicMovementBindings.Emplace(&movementTriggered);
	DynamicMovementBindings.Emplace(&movementCompleted);
	DynamicMovementBindings.Emplace(&jumpTriggered);
	DynamicMovementBindings.Emplace(&crouchTriggered);
	DynamicMovementBindings.Emplace(&crouchCompleted);
	
	
}

void AEVAPlayerController::SetMovementType(const EMovementType& MovementType)
{
	if (!ensureAlways(MovementComponent))
		return;

	CurrentMovementType = MovementType;
	
	switch (CurrentMovementType)
	{
		case EMovementType::VE_EVA:
			MovementComponent->GravityScale = 0;
			MovementComponent->SetMovementMode(MOVE_Flying);
			ConfigureEvaMovement();
			break;
		
		case EMovementType::VE_Walking:
			MovementComponent->SetMovementMode(MOVE_Walking);
			MovementComponent->GravityScale = 1;
			ConfigureRegularMovement();
			break;
		
		default: break;
	}
}

void AEVAPlayerController::ToggleEva()
{
	// Toggle between EVA and Walking
	SetMovementType(CurrentMovementType == EMovementType::VE_EVA ? EMovementType::VE_Walking : EMovementType::VE_EVA);
}

void AEVAPlayerController::Move(const FInputActionValue& Value)
{
	const FVector Input = Value.Get<FVector>();
	MovementVector = FVector(Input.Y, Input.X, 0); // adjust mapping

	const FRotator FacingDirection = GetActorRotation();
	const FVector ForwardMoveVector = MovementVector.X * UKismetMathLibrary::GetForwardVector(FacingDirection);
	const FVector RightMoveVector = MovementVector.Y * UKismetMathLibrary::GetRightVector(FacingDirection); 

	MovementVector = FVector(ForwardMoveVector.X + RightMoveVector.X,
		ForwardMoveVector.Y + RightMoveVector.Y,0);
	if (MovementVector.Length() > 0)
		MovementVector/=2;

	AddMovementInput(MovementVector);
}

void AEVAPlayerController::MoveEva(const FInputActionValue& Value)
{
	const FVector Input = Value.Get<FVector>();
	MovementVector = FVector(Input.Y, Input.X, 0); // adjust mapping

	const FRotator FacingDirection = GetActorRotation();
	const FVector ForwardMoveVector = MovementVector.X * UKismetMathLibrary::GetForwardVector(FacingDirection);
	const FVector RightMoveVector = MovementVector.Y * UKismetMathLibrary::GetRightVector(FacingDirection);
	
	MovementVector = FVector(ForwardMoveVector.X + RightMoveVector.X,
		ForwardMoveVector.Y + RightMoveVector.Y,0);
	if (MovementVector.Length() > 0)
		MovementVector/=2;
	
	MovementComponent->AddForce(MovementVector * EvaDesignData->EvaMovementSpeed);
}

void AEVAPlayerController::Look(const FInputActionValue& Value)
{
	RotationVector = Value.Get<FVector>();
	
	// apply movement frame
	AddControllerYawInput(RotationVector.X);
	AddControllerPitchInput(-RotationVector.Y);
}

void AEVAPlayerController::Interact(const FInputActionValue& Value)
{
	if (ActiveTool)
		ActiveTool->Use();
}

void AEVAPlayerController::Jump(const FInputActionValue& Value)
{
	MovementComponent->AddForce(FVector(0,0, MovementComponent->AirControl * EvaDesignData->EvaMovementSpeed));
}
void AEVAPlayerController::JumpHandlerEva(const FInputActionValue& Value)
{
	Jump(Value);
	Super::Jump();
}

void AEVAPlayerController::Crouch(const FInputActionValue& Value)
{
	MovementComponent->bWantsToCrouch = Value.Get<bool>();
}

void AEVAPlayerController::CrouchEva(const FInputActionValue& Value)
{
	MovementComponent->AddForce(FVector(0,0, MovementComponent->AirControl * -EvaDesignData->EvaMovementSpeed));
}

void AEVAPlayerController::DetermineHover()
{
	const FVector StartLocation = CameraReference->GetComponentLocation();

	TArray<FHitResult> Results;
	GetWorld()->LineTraceMultiByObjectType(Results, StartLocation, StartLocation + CameraReference->GetForwardVector() * EvaDesignData->LineTraceLength, FCollisionObjectQueryParams::AllDynamicObjects);

	AInteractable* NewHoveredInteractable = nullptr;
	for (auto HitResult : Results)
	{
		AActor* HitActor = HitResult.GetActor();
	
		if (HitActor == this)
			continue;

		if (HitActor)
		{
			NewHoveredInteractable = Cast<AInteractable>(HitActor);
			break;
		}		
	}

	ChangeHoveredInteractable(NewHoveredInteractable);
	
	if (ActiveTool)
		ActiveTool->UpdateHoveredInteractable(NewHoveredInteractable);
}

void AEVAPlayerController::ChangeHoveredInteractable(AInteractable* Interactable)
{
	if (HoveredInteractable != Interactable)
	{
		HoveredInteractable = Interactable;
		HoveredChangedDelegate.Broadcast(Interactable);
	}
}