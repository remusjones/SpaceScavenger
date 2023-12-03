// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACCLIProcessor.generated.h"


class AAHackable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESCAVENGER_API UACCLIProcessor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACCLIProcessor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	static void BreakInput(FString Input, FString& Command, TArray<FString>& Args);
	
	UFUNCTION(BlueprintCallable)
	virtual FString ProcessCommand(TArray<FString> Args);

	UFUNCTION(BlueprintCallable)
	virtual bool ProcessListCommand(TArray<AAHackable*> ObjectsToList, TArray<FString> Args, FString& ObjectsAvailable);	
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CommandNamespace = "default";

	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FString ListArgument = "list"; // TODO: Make this a CLI Processor
	
};
