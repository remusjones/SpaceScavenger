// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

	// Extract Rotation, create new rotation from input.
	// Get Forward, and Right axis and scale movement by axis
	// apply movement frame

	FVector FramePositionVector = MovementVector;
	const FVector FrameRotationVector = RotationVector * RotationScalar * DeltaTime;
	
	const FRotator RotatorOriginal = GetActorRotation();
	const FRotator NewRotation = FRotator(
		FMath::ClampAngle(RotatorOriginal.Pitch + FrameRotationVector.Y,
		PitchClampLower, PitchClampUpper),
		RotatorOriginal.Yaw + FrameRotationVector.X, RotatorOriginal.Roll);
	

	const FVector ForwardMoveVector = FramePositionVector.X * GetActorForwardVector();
	const FVector RightMoveVector = FramePositionVector.Y * GetActorRightVector(); 
	
	FramePositionVector = FVector(ForwardMoveVector.X + RightMoveVector.X,
		ForwardMoveVector.Y + RightMoveVector.Y,
		0);
	
	FramePositionVector.Normalize();
	SetActorLocationAndRotation(GetActorLocation()
		+ FramePositionVector * MovementScalar * DeltaTime,
		NewRotation, true);
	

	
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
		
		Input->BindAction(LookAction, ETriggerEvent::Triggered,this, &AAPlayerController::Look);
		Input->BindAction(LookAction, ETriggerEvent::Completed,this, &AAPlayerController::Look);
	}
}


void AAPlayerController::Move(const FInputActionValue& Value)
{
	FVector Input = Value.Get<FVector>();
	MovementVector = FVector(Input.Y, Input.X, 0); // adjust mapping
}

void AAPlayerController::Look(const FInputActionValue& Value)
{
	RotationVector = Value.Get<FVector>();
}
