// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HandItemsDataAsset.generated.h"


class IPlayerHandItem;

UENUM(BlueprintType)
enum class EHandType : uint8
{
	VE_None UMETA(DisplayName = "None"),
	VE_HackTool UMETA(DisplayName = "HackTool"),
	VE_PlasmaGun UMETA(DisplayName = "PlasmaGun"),
};

UCLASS(Blueprintable)
class SPACESCAVENGER_API UHandItemsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	AActor* CreateHandItem(const AActor* WorldContext, EHandType HandType) const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Hand Items", meta = (AllowPrivateAccess = "true"))
	TMap<EHandType, TSubclassOf<AActor>> HandItemsMap;
	
};