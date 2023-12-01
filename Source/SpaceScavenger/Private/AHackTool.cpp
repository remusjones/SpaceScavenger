// Fill out your copyright notice in the Description page of Project Settings.


#include "AHackTool.h"

#include "AHackable.h"
#include "AInteractable.h"
#include "Components/TimelineComponent.h"

// Sets default values
AAHackTool::AAHackTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAHackTool::BeginPlay()
{
	Super::BeginPlay();
	ConfigureTimeline();
}
void AAHackTool::ConfigureTimeline()
{

	HackingTimeline = NewObject<UTimelineComponent>(this, "Hacking Timeline");
	HackingTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
	this->BlueprintCreatedComponents.Add(HackingTimeline); 
	HackingTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
	HackingTimeline->SetDirectionPropertyName(FName("TimelineDirection"));
	
	HackingTimeline->SetLooping(false);
	HackingTimeline->SetTimelineLength(5.0f);
	HackingTimeline->SetTimelineLengthMode(TL_LastKeyFrame);
	HackingTimeline->SetPlaybackPosition(0.0f, false);

	FOnTimelineEventStatic OnTimelineFinishedCallback;
	OnTimelineFinishedCallback.BindUObject(this, &AAHackTool::FinishedHacking);
	FOnTimelineFloat OnTimelineCallback;
	OnTimelineCallback.BindUFunction(this, FName("HackingTick"));
	
	HackingTimeline->SetTimelineFinishedFunc(OnTimelineFinishedCallback);
	HackingTimeline->AddInterpFloat(HackingCurve, OnTimelineCallback);
	HackingTimeline->RegisterComponent();
	
}
// Called every frame
void AAHackTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HackingTimeline)
	{
		HackingTimeline->TickComponent(DeltaTime, LEVELTICK_TimeOnly, nullptr);
	}
}

void AAHackTool::UpdateDisplay(AAInteractable* HoveredInteractable)
{
	LastHovered = HoveredInteractable;

	if (ActiveToolState != EToolState::Idle)
		return;


	if (const AAHackable* Hackable = Cast<AAHackable>(HoveredInteractable); Hackable && Hackable->RequiresHack)
		DisplayTextChangedDelegate.Broadcast(HackableStatusMessages.FindRef(EHackableState::Locked));
	else if (!Hackable && !HoveredInteractable)
		DisplayTextChangedDelegate.Broadcast(ToolStatusMessages.FindRef(EToolState::Idle));
	else 
		DisplayTextChangedDelegate.Broadcast(HackableStatusMessages.FindRef(EHackableState::Unlocked));
		
}

void AAHackTool::TryInteract(AAInteractable* TargetInteractable)
{
	AAHackable* Hackable = Cast<AAHackable>(TargetInteractable);
	
	switch (ActiveToolState)
	{
		case EToolState::Idle:
			Hackable ? BeginHacking(Hackable) : TargetInteractable->Interact();
			break;
		case EToolState::Hacking:
			break;
		default: ;
	}
}

void AAHackTool::FinishedHacking()
{
	CurrentHackable->HackComplete();
	CurrentHackable->AttachCable(nullptr);
	CurrentHackable = nullptr;
	ActiveToolState = EToolState::Idle;
	UpdateDisplay(LastHovered);
}

void AAHackTool::HackingTick(float HackPercentage)
{
	HackPercentageDelegate.Broadcast(HackPercentage);
}

void AAHackTool::BeginHacking(AAHackable* TargetHackable)
{
	ActiveToolState = EToolState::Hacking;
	CurrentHackable = TargetHackable;
	CurrentHackable->AttachCable(ConnectionPoint);
	DisplayTextChangedDelegate.Broadcast(ToolStatusMessages.FindRef(ActiveToolState));	
	HackingCurve->FloatCurve.Keys.Last().Time = TargetHackable->HackDifficulty;
	HackingTimeline->SetTimelineLength(TargetHackable->HackDifficulty);
	HackingTimeline->PlayFromStart();
}
