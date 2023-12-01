// Fill out your copyright notice in the Description page of Project Settings.


#include "AHackable.h"
#include "CableComponent.h"
#include "NiagaraComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
AAHackable::AAHackable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAHackable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAHackable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FVector> Locations;
	CableComponent->GetCableParticleLocations(Locations);
	DisconnectEffect->SetWorldLocation(Locations.Last());
}

void AAHackable::AttachCable(UActorComponent* Target)
{
	if (Target)
	{
		CableComponent->SetAttachEndTo(Target->GetOwner(), Target->GetFName());
		CableComponent->SetVisibility(true);
		CableComponent->bEnableCollision = false;
		CableComponent->bAttachEnd = true;
		CableComponent->CableLength = CableLengthHacking;
	}
	else
	{
		CableComponent->bAttachEnd = false;
		CableComponent->SetAttachEndTo(nullptr, "");
		CableComponent->bEnableCollision = true;
		CableComponent->CableLength = CableLengthResting;
	
		if (DisconnectEffect)	
			DisconnectEffect->Activate(true);
	}
}

void AAHackable::HackStarted()
{

}

void AAHackable::HackComplete()
{
	if (HackOnce)
		RequiresHack = false;
	Interact();
}

