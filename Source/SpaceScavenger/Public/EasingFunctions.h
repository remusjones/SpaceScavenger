// Fill out your copyright notice in the Description page of Project Settings.
// https://easings.net

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunctions.generated.h"

/**
 * 
 */
UCLASS()
class SPACESCAVENGER_API UEasingFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static float EaseInSine(const float Input);
	static float EaseOutSine(const float Input);
	static float EaseInOutSine(const float Input);
	
	static float EaseInQuad(const float Input);
	static float EaseOutQuad(const float Input);
	static float EaseInOutQuad(const float Input);
	
	static float EaseInCubic(const float Input);
	static float EaseOutCubic(const float Input);
	static float EaseInOutCubic(const float Input);

	static float EaseInQuart(const float Input);
	static float EaseOutQuart(const float Input);
	static float EaseInOutQuart(const float Input);

	static float EaseInOutQuint(const float Input);
	static float EaseInOutExpo(const float Input);
	static float EaseInOutCirc(const float Input);
	static float EaseInOutBack(const float Input);
	static float EaseInOutElastic(const float Input);
};
