// Copyright Epic Games, Inc. All Rights Reserved.


#include "GenericFPSGameModeBase.h"

void AGenericFPSGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine!=nullptr);

	//display a debug message for five seconds
	//the -1 "key" value argument prevents the message from being updated or refreshed
	GEngine -> AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world!"));
}
