// Fill out your copyright notice in the Description page of Project Settings.


#include "AHackTool.h"

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
	
}

// Called every frame
void AAHackTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAHackTool::UpdateDisplay(AAInteractable* HoveredInteractable)
{
}

void AAHackTool::BeginHack(AAInteractable* TargetInteractable)
{
}