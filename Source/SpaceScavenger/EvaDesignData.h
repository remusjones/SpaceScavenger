// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EvaDesignData.generated.h"

/**
 * 
 */
UCLASS()
class SPACESCAVENGER_API UEvaDesignData : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	float AirControl = 0.66;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	float WalkSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	float CrouchWalkSpeed = 150;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	float CrouchSpeed = 15.0f;
};
