// Fill out your copyright notice in the Description page of Project Settings.


#include "HandItemsDataAsset.h"


AActor* UHandItemsDataAsset::CreateHandItem(const AActor* WorldContext, const EHandType HandType) const
{
	check(WorldContext);
	if (ensureAlways(HandItemsMap.Contains(HandType)))
	{
		const TSubclassOf<AActor> ItemClass = HandItemsMap[HandType];
		
		if (UWorld* World = WorldContext->GetWorld())
		{
			const FActorSpawnParameters SpawnParams;
			AActor* Item = World->SpawnActor<AActor>(ItemClass, SpawnParams);
			return Item;
		}
		return nullptr;
	}
	return nullptr;
}