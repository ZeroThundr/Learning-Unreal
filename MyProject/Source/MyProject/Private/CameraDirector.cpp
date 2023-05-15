// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
bool cameraIsOne;
float cameraHoldTime;
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	cameraIsOne = true;
	cameraHoldTime=CameraOne.holdTime;
}


// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if(cameraIsOne)
	{
		cameraHoldTime=CameraOne.holdTime;
	}else
	{
		cameraHoldTime=CameraTwo.holdTime;
	}
	TimeToNextCameraChange -= DeltaTime;
	if(TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange+=cameraHoldTime;
		//find the actor that handles control for the local player
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this,0);
		if(OurPlayerController)
		{
			if((OurPlayerController -> GetViewTarget()!= CameraOne.Camera)&&(CameraOne.Camera!=nullptr))
			{
				//smooth cut to camera one
				cameraIsOne=true;
				OurPlayerController -> SetViewTargetWithBlend(CameraOne.Camera,CameraOne.blendSpeed);
			}
			else if((OurPlayerController -> GetViewTarget()!=CameraTwo.Camera)&&(CameraTwo.Camera!=nullptr))
			{
				//blend smoothly to camera two
				cameraIsOne=false;
				OurPlayerController -> SetViewTargetWithBlend(CameraTwo.Camera,CameraTwo.blendSpeed);
			}
		}
	}
}

