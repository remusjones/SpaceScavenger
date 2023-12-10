// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHackTool.generated.h"

namespace ETimelineDirection
{
	enum Type : int;
}

class AAHackable;
class AAInteractable;
class UTimelineComponent;
UENUM(BlueprintType)

enum class EToolState : uint8 {
	None = 0,
	Idle = 1 UMETA(DisplayName = "Idle"),
	Hacking = 2  UMETA(DisplayName = "Hacking")
};

UENUM(BlueprintType)
enum class EHackableState : uint8 {
	None, 
	Unlocked = 1 UMETA(DisplayName = "Unlocked"),
	Locked = 2  UMETA(DisplayName = "Locked")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackPercentageDelegate, float, HackPercentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisplayTextChangedDelegate, FText, DisplayText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHackInterrupted);
UCLASS()
class SPACESCAVENGER_API AAHackTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHackTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ConfigureTimeline();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateDisplay(AAInteractable* HoveredInteractable);
	virtual void TryInteract(AAInteractable* TargetInteractable);
	virtual void BeginHacking(AAHackable* TargetHackable);
	virtual void FinishedHacking();
	virtual void InterruptHacking();
	
	
	UFUNCTION()
	virtual void HackingTick(float HackPercentage);

	// Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* HackingCurve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ConnectionPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EToolState, FText> ToolStatusMessages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EHackableState, FText> HackableStatusMessages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumHackingLength = 200;
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FHackPercentageDelegate HackPercentageDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FDisplayTextChangedDelegate DisplayTextChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FHackInterrupted HackInterruptedDelegate;

	UPROPERTY()
	float InterpFloatCurve;
	UPROPERTY(BlueprintReadOnly)
	bool IsHacking;
	UPROPERTY(BlueprintReadOnly)	
	AAHackable* CurrentHackable;
	UPROPERTY(BlueprintReadOnly)
	AAInteractable* LastHovered;
private:

	// Cached Variables
	EToolState ActiveToolState = EToolState::Idle;
	UPROPERTY()
	UTimelineComponent* HackingTimeline;
	
};