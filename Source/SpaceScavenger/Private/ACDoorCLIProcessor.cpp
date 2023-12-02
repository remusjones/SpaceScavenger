// Fill out your copyright notice in the Description page of Project Settings.


#include "ACDoorCLIProcessor.h"
#include "AHackable.h"

FString UACDoorCLIProcessor::ProcessCommand(TArray<FString> Args)
{
	if (FString ListOutput; ProcessListCommand(AccessibleInteractables, Args, ListOutput))
		return ListOutput;
	
	if (Args.Num() > 0)
	{
		for (const auto Hackable : AccessibleInteractables)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Hackable->Identifier.ToString());
			if (Hackable->Identifier.ToLower().ToString() == Args[0])
			{
				if (Hackable->TryInteract())
					return FString::Printf(TEXT("Accessing Door: %s"), *Args[0]);
				return FString::Printf(TEXT("Door Locked: %s"), *Args[0]);
			}
		}
		return FString::Printf(TEXT("Door Inaccessable: %s"), *Args[0]);
	}
	return FString::Printf(TEXT("ERROR: Incorrect Args"));	
}
