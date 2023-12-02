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
	virtual FString ProcessCommand(TArray<FString> Args) override;
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AAHackable*> AccessibleInteractables;
};
