// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerHandItem.generated.h"

class AInteractable;
// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UPlayerHandItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPACESCAVENGER_API IPlayerHandItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Use() = 0;
	virtual void UseHold() = 0;
	virtual void UseRelease() = 0;
	virtual void UpdateHoveredInteractable(AInteractable* HoveredInteractable) = 0;
};
