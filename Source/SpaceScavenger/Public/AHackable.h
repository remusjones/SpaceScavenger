// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AInteractable.h"
#include "GameFramework/Actor.h"
#include "AHackable.generated.h"

UENUM(BlueprintType)
enum class HackableState : uint8 {
	Unlocked = 0 UMETA(DisplayName = "Unlocked"),
	Locked = 1  UMETA(DisplayName = "Locked")
};

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

	void HackStarted();
	UFUNCTION(BlueprintCallable)
	void HackComplete();

	UPROPERTY(BlueprintReadWrite)
	bool RequiresHack = true;
	UPROPERTY(BlueprintReadWrite)
	bool HackOnce = true;	
	UPROPERTY(BlueprintReadWrite)
	UCableComponent* CableComponent;
};