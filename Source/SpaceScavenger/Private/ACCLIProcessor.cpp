// Fill out your copyright notice in the Description page of Project Settings.


#include "ACCLIProcessor.h"

#include "AHackable.h"

// Sets default values for this component's properties
UACCLIProcessor::UACCLIProcessor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACCLIProcessor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UACCLIProcessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACCLIProcessor::BreakInput(const FString Input, FString& Command,
                                 TArray<FString>& Args)
{
	TArray<FString> SplitArray;

	// split
	Input.ParseIntoArray(SplitArray, TEXT(" "));

	// Early exit
	if (SplitArray.Num() == 0)
	{
		Command = Input.ToLower();
		return;
	}

	Command = SplitArray[0].ToLower();

	// early exit
	if (SplitArray.Num() == 1) 
		return;

	// Populate remainder of the arguments
	Args.SetNum(SplitArray.Num() - 1);
	for(int i = 1; i < SplitArray.Num(); i++)
	{
		Args[i - 1] = SplitArray[i].ToLower();	
	}
	
}

void UACCLIProcessor::RegisterCommand(const FString Command, const FProcessCommandDelegate& Callback)
{
	if (CommandProcessorMap.Contains(Command))
	{
		CommandProcessorMap[Command].Add(Callback);
	}else
	{
		CommandProcessorMap.Add(Command, TArray{Callback});
	}
}

void UACCLIProcessor::UnregisterCommand(const FString Command, const FProcessCommandDelegate& Callback)
{
	if (CommandProcessorMap.Contains(Command))
	{
		CommandProcessorMap[Command].Remove(Callback);
		if (CommandProcessorMap[Command].Num() == 0)
			CommandProcessorMap.Remove(Command);
	}
}


FString UACCLIProcessor::ProcessCommand(TArray<FString> Args)
{
	if (Args.Num() > 0)
	{
		FString Final;
		if (CommandProcessorMap.Contains(Args[0]))
		{
			for (auto ProcessCommandDelegate : CommandProcessorMap[Args[0]])
			{
				if (!ProcessCommandDelegate.IsBound())
					continue;
				
				FString CommandOutput;
				TArray<FString> subArguments = TArray<FString>();
				if (Args.Num() > 1)
				{
					subArguments.SetNumUninitialized(Args.Num()-1);
					for(int i = 1; i < Args.Num(); i++)
					{
						subArguments[i - 1] = Args[i];
					}
				}
				CommandOutput = ProcessCommandDelegate.Execute(subArguments);
				if (CommandOutput.Len() > 0)
					Final.Append(CommandOutput).Append("\n");
			}
		}
		if (Final.Len() > 0)
		{
			Final.RemoveFromEnd("\n");
			return Final;
		}
	}
	return {"ERROR"};
}

bool UACCLIProcessor::ProcessListCommand(TArray<AAHackable*> ObjectsToList,
	TArray<FString> Args, FString& ObjectsAvailable)
{
	if (Args.Num() == 0)
		return false;
	if (Args[0] != ListArgument)
		return false;
	
	for(int i = 0; i < ObjectsToList.Num(); i++)
	{
		ObjectsAvailable.Append(ObjectsToList[i]->Identifier.ToString());
		if (i < ObjectsToList.Num() - 1)
			ObjectsAvailable.Append(", ");
	}
	return true;
}