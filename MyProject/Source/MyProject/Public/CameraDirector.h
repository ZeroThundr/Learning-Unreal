// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "tiff.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT()
struct FCameraStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category="Cameras")
	AActor* Camera;
	UPROPERTY(EditAnywhere, Category="BlendSpeeds")
	float blendSpeed;
	UPROPERTY(EditAnywhere,Category="Camera Time")
	float holdTime;
};
UCLASS()
class MYPROJECT_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	float TimeToNextCameraChange;

	UPROPERTY(EditAnywhere)
	FCameraStruct CameraOne;
	UPROPERTY(EditAnywhere)
	FCameraStruct CameraTwo;

};


