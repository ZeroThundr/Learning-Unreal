// Fill out your copyright notice in the Description page of Project Settings.


#include "HowTo_Components.h"

// Sets default values
AHowTo_Components::AHowTo_Components()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHowTo_Components::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHowTo_Components::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHowTo_Components::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

