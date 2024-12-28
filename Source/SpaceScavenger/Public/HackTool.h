// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTool.h"
#include "GameFramework/Actor.h"
#include "HackTool.generated.h"

namespace ETimelineDirection
{
	enum Type : int;
}

class AHackable;
class AInteractable;
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackFinished, bool, Succeeded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHackStarted);
UCLASS()
class SPACESCAVENGER_API AHackTool : public AActor, public IPlayerTool
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHackTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ConfigureTimeline();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateDisplay(AInteractable* HoveredInteractable); // Replace with IPlayerTool::UpdateHoveredInteractable() override
	virtual void TryInteract(AInteractable* TargetInteractable); // Replace with IPlayerTool::Use() override
	virtual void BeginHacking(AHackable* TargetHackable); // Replace with IPlayerTool::Use() override
	virtual void FinishedHacking();
	virtual void InterruptHacking();

	virtual void Use() override;
	virtual void UseHold() override;
	virtual void UseRelease() override;
	virtual void UpdateHoveredInteractable(AInteractable* HoveredInteractable) override;
	
	
	
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
	FHackFinished HackFinishedDelegate;
	UPROPERTY(BlueprintAssignable)
	FHackStarted HackStartedDelegate;
	
	UPROPERTY()
	float InterpFloatCurve;
	UPROPERTY(BlueprintReadOnly)
	bool IsHacking;
	UPROPERTY(BlueprintReadOnly)	
	AHackable* CurrentHackable;
	UPROPERTY(BlueprintReadOnly)
	AInteractable* LastHovered;
private:

	// Cached Variables
	EToolState ActiveToolState = EToolState::Idle;
	UPROPERTY()
	UTimelineComponent* HackingTimeline;
	
};