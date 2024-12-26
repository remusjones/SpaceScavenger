// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Hackable.generated.h"



class UCableComponent;
class UNiagaraComponent;

UCLASS()
class SPACESCAVENGER_API AHackable : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHackable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AttachCable(UActorComponent* Target);
	virtual void DisableCableSimulation();
	void HackStarted();
	UFUNCTION(BlueprintCallable)
	void HackComplete();
	bool TryInteract();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool RequiresHack = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HackOnce = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool AutoInteractAfterHack = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Identifier;
	UPROPERTY(BlueprintReadWrite)
	UCableComponent* CableComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HackDifficulty = 3;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CableLengthHacking = 20;		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CableLengthResting = 50;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CableSimulationTimer = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraComponent* DisconnectEffect;

private:
	FTimerHandle CableTimerHandler;
};