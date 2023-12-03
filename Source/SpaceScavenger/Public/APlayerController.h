// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "APlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AAInteractable;
class AAHackTool;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoveredChangedDelegate, AAInteractable*, HoveredInteractable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackingDelegate, AAInteractable*, TargetInteractable);
//
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACESCAVENGER_API AAPlayerController : public ACharacter
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

	// Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput")
	UInputAction* InteractAction;

	
	// Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector MovementVector;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector RotationVector;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	USceneComponent* Test;	
	

	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	USceneComponent* LineTraceOrigin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float LineTraceLength = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	AAHackTool* HackTool; // Hack tool

	
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FInteractedDelegate InteractedDelegate;
	UPROPERTY(BlueprintAssignable)
	FHackingDelegate HackingDelegate;
	UPROPERTY(BlueprintAssignable)
	FHoveredChangedDelegate HoveredChangedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Overrides")
	float AirControl = 0.66;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Overrides")
	float WalkSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Overrides")
	float CrouchWalkSpeed = 150;

	
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void DetermineHover();
	void ChangeHoveredInteractable(AAInteractable* Interactable);
	
	UPROPERTY()	
	AAInteractable* HoveredInteractable;
	
};

