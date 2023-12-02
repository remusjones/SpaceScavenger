// Fill out your copyright notice in the Description page of Project Settings.


#include "ACDoorCLIProcessor.h"

#include "AInteractable.h"

FString UACDoorCLIProcessor::ProcessCommand(TArray<FString> Args)
{
	if (Args.Num() > 0)
	{
		for (const auto Interactable : AccessableInteractables)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Interactable->GetName());
			if (Interactable->GetName().ToLower() == Args[0])
			{
				Interactable->Interact();
				return FString::Printf(TEXT("Toggling Door: %s"), *Args[0]);
			}
		}
		return FString::Printf(TEXT("Invalid Door: %s"), *Args[0]);
	}
	return FString::Printf(TEXT("ERROR: Requires 1 Argument"));	
}
