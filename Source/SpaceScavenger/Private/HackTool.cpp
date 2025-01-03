// Fill out your copyright notice in the Description page of Project Settings.


#include "HackTool.h"
#include "Hackable.h"
#include "Interactable.h"
#include "Components/TimelineComponent.h"

// Sets default values
AHackTool::AHackTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHackTool::BeginPlay()
{
	Super::BeginPlay();
	ConfigureTimeline();
}

void AHackTool::ConfigureTimeline()
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
	OnTimelineFinishedCallback.BindUObject(this, &AHackTool::FinishedHacking);
	FOnTimelineFloat OnTimelineCallback;
	OnTimelineCallback.BindUFunction(this, FName("HackingTick"));
	
	HackingTimeline->SetTimelineFinishedFunc(OnTimelineFinishedCallback);
	HackingTimeline->AddInterpFloat(HackingCurve,OnTimelineCallback, "InterpFloatCurve");
	HackingTimeline->RegisterComponent();
	
}
// Called every frame
void AHackTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HackingTimeline)
	{
		HackingTimeline->TickComponent(DeltaTime, LEVELTICK_TimeOnly, nullptr);
	}
}

void AHackTool::UpdateDisplay(AInteractable* HoveredInteractable)
{

	if (ActiveToolState != EToolState::Idle)
		return;
	
	
	if (const AHackable* Hackable = Cast<AHackable>(HoveredInteractable); Hackable )
	{
		FFormatNamedArguments Args;
		Args.Add("State", HackableStatusMessages.FindRef(Hackable->RequiresHack
			? EHackableState::Locked
			: EHackableState::Unlocked));
		
		Args.Add("Identifier", Hackable->Identifier);	
		
		DisplayTextChangedDelegate.Broadcast(FText::Format(NSLOCTEXT("Tool","State","{Identifier}\n{State}"), Args));
	}
	else if (!Hackable && !HoveredInteractable)
		DisplayTextChangedDelegate.Broadcast(ToolStatusMessages.FindRef(EToolState::Idle));
	else                        
		DisplayTextChangedDelegate.Broadcast( HackableStatusMessages.FindRef(EHackableState::Unlocked));
		
}

void AHackTool::TryInteract(AInteractable* TargetInteractable)
{
	if (!TargetInteractable)
		return;
		
	AHackable* Hackable = Cast<AHackable>(TargetInteractable);
	
	switch (ActiveToolState)
	{
		case EToolState::Idle:
			Hackable && Hackable->RequiresHack ? BeginHacking(Hackable) : TargetInteractable->Interact();
			break;
		case EToolState::Hacking:
			break;
		default: ;
	}
}

void AHackTool::FinishedHacking()
{
	if (!CurrentHackable)
		return;
	
	CurrentHackable->HackComplete();
	InterruptHacking();
}

void AHackTool::InterruptHacking()
{
	if (!CurrentHackable)
		return;
	
	CurrentHackable->AttachCable(nullptr);
	CurrentHackable = nullptr;
	ActiveToolState = EToolState::Idle;
	UpdateDisplay(LastHovered);
	
	if (HackingTimeline->IsPlaying() && HackFinishedDelegate.IsBound())
		HackFinishedDelegate.Broadcast(false);
	else 
		HackFinishedDelegate.Broadcast(true);	
	HackingTimeline->Stop();
	IsHacking = false;
}

void AHackTool::Use()
{
	TryInteract(LastHovered);
}

void AHackTool::UseHold()
{
}

void AHackTool::UseRelease()
{
}

void AHackTool::UpdateHoveredInteractable(AInteractable* HoveredInteractable)
{
	LastHovered = HoveredInteractable;
	UpdateDisplay(HoveredInteractable);
}


void AHackTool::HackingTick(const float HackPercentage)
{
	HackPercentageDelegate.Broadcast(HackPercentage);

	if (!CurrentHackable || FVector::Dist(CurrentHackable->GetActorLocation(), ConnectionPoint->GetComponentLocation()) > MaximumHackingLength)
		InterruptHacking();
}

void AHackTool::BeginHacking(AHackable* TargetHackable)
{
	ActiveToolState = EToolState::Hacking;
	CurrentHackable = TargetHackable;
	CurrentHackable->AttachCable(ConnectionPoint);
	
	FFormatNamedArguments Args;
	Args.Add("Identifier", TargetHackable->Identifier);
	Args.Add("State", ToolStatusMessages.FindRef(ActiveToolState));
	DisplayTextChangedDelegate.Broadcast(FText::Format(NSLOCTEXT("Tool","State","{Identifier}\n{State}"), Args));

	const int KeysCount = HackingCurve->FloatCurve.Keys.Num();
	for(int i = 1; i < HackingCurve->FloatCurve.Keys.Num(); i++)
	{
		HackingCurve->FloatCurve.Keys[KeysCount- 1 - i].Time = TargetHackable->HackDifficulty / i-1; 
	}
	HackingTimeline->SetTimelineLength(TargetHackable->HackDifficulty);
	HackingTimeline->PlayFromStart();
	IsHacking = true;
	if (HackStartedDelegate.IsBound())
		HackStartedDelegate.Broadcast();
}

