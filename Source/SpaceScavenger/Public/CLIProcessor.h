// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CLIProcessor.generated.h"


class AHackable;
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString, FProcessCommandDelegate, const TArray<FString>&, Args);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESCAVENGER_API UCLIProcessor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCLIProcessor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	static void BreakInput(FString Input, FString& Command, TArray<FString>& Args);
	
	UFUNCTION(BlueprintCallable)
	virtual void RegisterCommand(const FString Command, const FProcessCommandDelegate& Callback);
	UFUNCTION(BlueprintCallable)
	virtual void UnregisterCommand(const FString Command, const FProcessCommandDelegate& Callback);
	UFUNCTION(BlueprintCallable)
	virtual bool ProcessCommand(TArray<FString> Args, FString& Output);

	UFUNCTION(BlueprintCallable)
	virtual bool ProcessListCommand(TArray<AHackable*> ObjectsToList, TArray<FString> Args, FString& ObjectsAvailable);	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CommandNamespace = "default";

	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FString ListArgument = "list";
	TMap<FString, TArray<FProcessCommandDelegate>> CommandProcessorMap;

};