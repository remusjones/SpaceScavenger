// Fill out your copyright notice in the Description page of Project Settings.


#include "AAirlockController.h"

#include "ADoor.h"

// Sets default values
AAAirlockController::AAAirlockController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAAirlockController::BeginPlay()
{
	Super::BeginPlay();
	check(InternalAirlock != nullptr)
	check(ExternalAirlock != nullptr);	
}

// Called every frame
void AAAirlockController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ECurrentAirlockState == AirlockCycling)
	{
		if (InternalStateTimer >= AirlockOxygenCycleTime + DoorCycleDelay)
		{
			UE_LOG(LogTemp, Warning, TEXT("Finalizing"));
			FinalizeStateChange();
		}
		else
			InternalStateTimer += DeltaTime;
		
			UE_LOG(LogTemp, Warning, TEXT("Ticking %f"), InternalStateTimer);
	}

}

void AAAirlockController::CycleAirlock()
{
	switch (ECurrentAirlockState)
	{
		case AirlockInternal:
			ETargetAirlockState = AirlockExternal;
			ECurrentAirlockState = AirlockCycling;
			break;
		case AirlockExternal:
			ETargetAirlockState = AirlockInternal;
			ECurrentAirlockState = AirlockCycling;
			break;
		case AirlockCycling:
			// Ignore
			break;
		default: ;
		
		ExternalAirlock->Close();
		InternalAirlock->Close();
	}
	if (AirlockStateChangedDelegate.IsBound())
		AirlockStateChangedDelegate.Broadcast(ECurrentAirlockState);
}

void AAAirlockController::FinalizeStateChange()
{
	InternalStateTimer = 0;
	ECurrentAirlockState = ETargetAirlockState;
	
	switch (ETargetAirlockState)
	{
		case AirlockInternal:
			InternalAirlock->Open();
		UE_LOG(LogTemp, Warning, TEXT("INTERNAL"))
			break;
		case AirlockExternal:
			ExternalAirlock->Open();
		UE_LOG(LogTemp, Warning, TEXT("EXTERNAL"))
			break;
		case AirlockCycling: break;
		default: ;
	}

	if (AirlockStateChangedDelegate.IsBound())
		AirlockStateChangedDelegate.Broadcast(ECurrentAirlockState);
}