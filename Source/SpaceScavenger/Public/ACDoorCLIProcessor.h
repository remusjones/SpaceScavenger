// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ACCLIProcessor.h"
#include "ACDoorCLIProcessor.generated.h"

class AAHackable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESCAVENGER_API UACDoorCLIProcessor : public UACCLIProcessor
{
	GENERATED_BODY()
	virtual bool ProcessCommand(TArray<FString> Args, FString& Output) override;
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AAHackable*> AccessibleInteractables;
};
