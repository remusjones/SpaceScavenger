// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AInteractable.h"
#include "GameFramework/Actor.h"
#include "AHackable.generated.h"




class UCableComponent;

UCLASS()
class SPACESCAVENGER_API AAHackable : public AAInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHackable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AttachCable(UActorComponent* Target);
	
	void HackStarted();
	UFUNCTION(BlueprintCallable)
	void HackComplete();

	UPROPERTY(BlueprintReadWrite)
	bool RequiresHack = true;
	UPROPERTY(BlueprintReadWrite)
	bool HackOnce = true;	
	UPROPERTY(BlueprintReadWrite)
	UCableComponent* CableComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HackDifficulty = 3;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CableLengthHacking = 20;		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CableLengthResting = 50;		
};