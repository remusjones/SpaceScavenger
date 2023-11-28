// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "APlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AAInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoveredChangedDelegate, AAInteractable*, HoveredInteractable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackingDelegate, AAInteractable*, TargetInteractable);
//
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACESCAVENGER_API AAPlayerController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* InteractAction;	
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector MovementVector;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector RotationVector;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MovementScalar = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float RotationScalar = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	USceneComponent* LineTraceOrigin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float LineTraceLength = 5;


	UPROPERTY(BlueprintAssignable)
	FInteractedDelegate InteractedDelegate;

	UPROPERTY(BlueprintAssignable)
	FHackingDelegate HackingDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FHoveredChangedDelegate HoveredChangedDelegate;
	
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void DetermineHover();
	void ChangeHoveredInteractable(AAInteractable* Interactable);
	void CalculateLocomotion(float DeltaTime);
	const float PitchClampLower = -89;
	const float PitchClampUpper = 89;

	AAInteractable* HoveredInteractable;

	
};

