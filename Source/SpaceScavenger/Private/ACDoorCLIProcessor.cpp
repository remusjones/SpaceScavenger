// Fill out your copyright notice in the Description page of Project Settings.


#include "ACDoorCLIProcessor.h"
#include "AHackable.h"

bool UACDoorCLIProcessor::ProcessCommand(TArray<FString> Args, FString& Output)
{
	if (Super::ProcessCommand(Args, Output))
		return true;
	if (ProcessListCommand(AccessibleInteractables, Args, Output))
		return true;
	
	
	if (Args.Num() > 0)
	{
		for (const auto Hackable : AccessibleInteractables)
		{
			if (Hackable->Identifier.ToLower().ToString() == Args[0])
			{
				if (Hackable->TryInteract())
				{
					Output = FString::Printf(TEXT("Accessing Door: %s"), *Args[0]);
					
				}
				Output = FString::Printf(TEXT("Door Locked: %s"), *Args[0]);
			}
		}
		Output = FString::Printf(TEXT("Door Inaccessable: %s"), *Args[0]);
	}
	Output = FString::Printf(TEXT("ERROR: Incorrect Args"));
	return true;	
}
