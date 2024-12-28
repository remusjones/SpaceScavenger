// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "EVAPlayerController.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
    VE_Walking UMETA(DisplayName = "None"),
    VE_EVA UMETA(DisplayName = "Eva"),
};


class IPlayerTool;
class UInputMappingContext;
class UInputAction;
class AInteractable;
class UEvaDesignData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHoveredChangedDelegate, AInteractable*, HoveredInteractable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackingDelegate, AInteractable*, TargetInteractable);
//
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACESCAVENGER_API AEVAPlayerController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEVAPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void ConfigureEvaMovement();
	void ConfigureRegularMovement();
	void SetMovementType(const EMovementType& MovementType);
	void ToggleEva();


	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	USceneComponent* CameraReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float LineTraceLength = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TScriptInterface<IPlayerTool> ActiveTool;
	
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FInteractedDelegate InteractedDelegate;
	UPROPERTY(BlueprintAssignable)
	FHackingDelegate HackingDelegate;
	UPROPERTY(BlueprintAssignable)
	FHoveredChangedDelegate HoveredChangedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	TSoftObjectPtr<UEvaDesignData> EvaDesignData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Overrides")
	EMovementType CurrentMovementType = EMovementType::VE_Walking;
	UPROPERTY(BlueprintReadOnly)	
	AInteractable* HoveredInteractable;

	
private:
	
	void Move(const FInputActionValue& Value);
	void MoveEva(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void JumpHandlerEva(const FInputActionValue& Value);
	void Crouch(const FInputActionValue& Value);
	void CrouchEva(const FInputActionValue& Value);
	void DetermineHover();
	void ChangeHoveredInteractable(AInteractable* Interactable);


private:

	// Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	
	// Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector MovementVector;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector RotationVector;	


	
	float EvaMovementSpeed = 10000;
	float CrouchNorm = 1.0f;
	float DefaultCapsuleHalfHeight = 88.0f;
	UPROPERTY() 
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY()
	UCapsuleComponent* BodyCapsuleComponent;

	
	TArray<FEnhancedInputActionEventBinding*> DynamicMovementBindings;

	FInputActionBinding MoveBinding;
	FInputActionBinding JumpBinding;
	FInputActionBinding CrouchBinding;
	FInputActionBinding InteractBinding;
	FInputActionBinding LookBinding;

	
};