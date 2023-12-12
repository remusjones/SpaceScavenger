// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorStateChangedDelegate, bool, State);
UCLASS()
class SPACESCAVENGER_API AADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void Toggle();
	UFUNCTION(BlueprintCallable)
	void Open();
	UFUNCTION(BlueprintCallable)
	void Close();
	UFUNCTION(BlueprintCallable)
	void SetState(bool NewState);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bState = true;

	UPROPERTY(BlueprintAssignable)
	FDoorStateChangedDelegate DoorStateChangedDelegate;
};