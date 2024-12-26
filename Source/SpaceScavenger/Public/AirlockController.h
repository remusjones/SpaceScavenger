// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirlockController.generated.h"

UENUM(BlueprintType)
enum EAirlockState 
{
	AirlockInternal,
	AirlockExternal,
	AirlockCycling
};

class ADoor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAirlockStateChangedDelegate, EAirlockState, AirlockState);
UCLASS()
class SPACESCAVENGER_API AAirlockController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAirlockController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void CycleAirlock();
	void FinalizeStateChange();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DoorCycleDelay = 2.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AirlockOxygenCycleTime = 5.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)                                             
	ADoor* ExternalAirlock;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ADoor* InternalAirlock;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAirlockState> ECurrentAirlockState;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAirlockState> ETargetAirlockState;

	float InternalStateTimer = 0.0f;

	
	UPROPERTY(BlueprintAssignable)
	FAirlockStateChangedDelegate AirlockStateChangedDelegate;
	
};