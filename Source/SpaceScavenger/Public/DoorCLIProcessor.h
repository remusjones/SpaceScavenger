// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CLIProcessor.h"
#include "DoorCLIProcessor.generated.h"

class AHackable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESCAVENGER_API UDoorCLIProcessor : public UCLIProcessor
{
	GENERATED_BODY()
	virtual bool ProcessCommand(TArray<FString> Args, FString& Output) override;
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AHackable*> AccessibleInteractables;
};
