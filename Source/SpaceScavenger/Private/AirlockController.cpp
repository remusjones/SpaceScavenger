// Fill out your copyright notice in the Description page of Project Settings.


#include "AirlockController.h"

#include "Door.h"

// Sets default values
AAirlockController::AAirlockController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirlockController::BeginPlay()
{
	Super::BeginPlay();
	check(InternalAirlock != nullptr)
	check(ExternalAirlock != nullptr);	
}

// Called every frame
void AAirlockController::Tick(float DeltaTime)
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

void AAirlockController::CycleAirlock()
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
		

	}
	ExternalAirlock->Close();
	InternalAirlock->Close();
	if (AirlockStateChangedDelegate.IsBound())
		AirlockStateChangedDelegate.Broadcast(ECurrentAirlockState);
}

void AAirlockController::FinalizeStateChange()
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