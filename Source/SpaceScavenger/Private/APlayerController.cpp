// Fill out your copyright notice in the Description page of Project Settings.
#include "APlayerController.h"

#include "AHackTool.h"
#include "AInteractable.h"
#include "EasingFunctions.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAPlayerController::AAPlayerController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = WalkSpeed;
	MovementComponent->MaxWalkSpeedCrouched = CrouchWalkSpeed;
	MovementComponent->AirControl = AirControl;
	MovementComponent->NavAgentProps.bCanCrouch = true;
	BodyCapsuleComponent = GetCapsuleComponent(); 
	DefaultCapsuleHalfHeight = BodyCapsuleComponent->GetUnscaledCapsuleHalfHeight();

	
	RecalculateCrouchedEyeHeight();
}


// Called every frame
void AAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetermineHover();

	if (bIsEva)
	{
		MovementComponent->GravityScale = 0;
		MovementComponent->SetMovementMode(MOVE_Flying);
	}
	else
	{
		MovementComponent->SetMovementMode(MOVE_Walking);
		MovementComponent->GravityScale = 1;
	}
	
	if (bIsCrouching)
		CrouchNorm = FMathf::Clamp(CrouchNorm - (CrouchSpeed * DeltaTime), 0, 1);
	else		
		CrouchNorm = FMathf::Clamp(CrouchNorm + (CrouchSpeed * DeltaTime), 0, 1);
	
	BodyCapsuleComponent->SetCapsuleHalfHeight(FMath::Lerp(CrouchedEyeHeight,DefaultCapsuleHalfHeight, UEasingFunctions::EaseInOutExpo(CrouchNorm)));
}


// Called to bind functionality to input
void AAPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(MoveAction, ETriggerEvent::Triggered,this, &AAPlayerController::Move);
		Input->BindAction(MoveAction, ETriggerEvent::Completed,this, &AAPlayerController::Move);
		
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AAPlayerController::JumpHandler);
		
		Input->BindAction(LookAction, ETriggerEvent::Triggered,this, &AAPlayerController::Look);
		Input->BindAction(LookAction, ETriggerEvent::Completed,this, &AAPlayerController::Look);

		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AAPlayerController::Interact);

		Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AAPlayerController::CrouchHandler);
		Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AAPlayerController::CrouchHandler);	
	}
}

void AAPlayerController::Move(const FInputActionValue& Value)
{
	const FVector Input = Value.Get<FVector>();
	MovementVector = FVector(Input.Y, Input.X, 0); // adjust mapping

	const FRotator FacingDirection = GetActorRotation();
	const FVector ForwardMoveVector = MovementVector.X * UKismetMathLibrary::GetForwardVector(FacingDirection);
	const FVector RightMoveVector = MovementVector.Y * UKismetMathLibrary::GetRightVector(FacingDirection); 
	//
	MovementVector = FVector(ForwardMoveVector.X + RightMoveVector.X,
		ForwardMoveVector.Y + RightMoveVector.Y,0);
	MovementVector.Normalize();
	if (bIsEva)
	{
		MovementVector *= AirControl;
		AddMovementInput(MovementVector);
		//AddMovementInput(MovementVector);
	}else
		AddMovementInput(MovementVector);
		
}

void AAPlayerController::Look(const FInputActionValue& Value)
{
	RotationVector = Value.Get<FVector>();
	
	// apply movement frame
	AddControllerYawInput(RotationVector.X);
	AddControllerPitchInput(-RotationVector.Y);
}

void AAPlayerController::Interact(const FInputActionValue& Value)
{
	if (HoveredInteractable)
		HackTool->TryInteract(HoveredInteractable);
}

void AAPlayerController::JumpHandler(const FInputActionValue& Value)
{
	if (!bIsEva)
		Super::Jump();
	else
	{
		AddMovementInput(FVector(0,0, AirControl));
	}
}

void AAPlayerController::CrouchHandler(const FInputActionValue& Value)
{
	bIsCrouching = Value.Get<bool>();
	if (bIsEva)
	{
		AddMovementInput(FVector(0,0, -AirControl));
	}
}

void AAPlayerController::DetermineHover()
{
	const FVector StartLocation = CameraReference->GetComponentLocation();

	TArray<FHitResult> Results;
	GetWorld()->LineTraceMultiByObjectType(Results, StartLocation, StartLocation + CameraReference->GetForwardVector() * LineTraceLength, FCollisionObjectQueryParams::AllDynamicObjects);


	AAInteractable* NewHoveredInteractable = nullptr;
	for (auto HitResult : Results)
	{
		AActor* HitActor = HitResult.GetActor();
	
		if (HitActor == this)
			continue;

		if (HitActor)
		{
			NewHoveredInteractable = Cast<AAInteractable>(HitActor);
			
			break;
		}		
	}

	ChangeHoveredInteractable(NewHoveredInteractable);
	HackTool->UpdateDisplay(NewHoveredInteractable);
}

void AAPlayerController::ChangeHoveredInteractable(AAInteractable* Interactable)
{
	if (HoveredInteractable != Interactable)
	{
		HoveredInteractable = Interactable;
		HoveredChangedDelegate.Broadcast(Interactable);
	}
}