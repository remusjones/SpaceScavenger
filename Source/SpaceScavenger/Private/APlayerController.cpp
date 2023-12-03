// Fill out your copyright notice in the Description page of Project Settings.
#include "APlayerController.h"

#include "AHackTool.h"
#include "AInteractable.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
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
}

// Called every frame
void AAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateLocomotion(DeltaTime);
	DetermineHover();	
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
		
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &Super::Jump);
		
		Input->BindAction(LookAction, ETriggerEvent::Triggered,this, &AAPlayerController::Look);
		Input->BindAction(LookAction, ETriggerEvent::Completed,this, &AAPlayerController::Look);

		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AAPlayerController::Interact);
		
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

void AAPlayerController::DetermineHover()
{
	const FVector StartLocation = LineTraceOrigin->GetComponentLocation();
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation,
		StartLocation + LineTraceOrigin->GetForwardVector() * LineTraceLength,
		ECC_WorldDynamic);
	AAInteractable* NewHoveredInteractable = nullptr;
	
	if (HitResult.GetActor())
	{
		NewHoveredInteractable = Cast<AAInteractable>(
			HitResult.GetActor());
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

void AAPlayerController::CalculateLocomotion(const float DeltaTime)
{
}

