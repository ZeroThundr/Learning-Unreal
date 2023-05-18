// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;

UCLASS()
class GENERICFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category= Camera, meta=(AllowPrivateAccess="true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input, meta=(AllowPrivateAccess="True"))
	UInputAction* FireAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input,meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	AFPSCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AFPSProjectile> ProjectileClass;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
public:
	USkeletalMeshComponent* GetMesh1P() const {return Mesh1P;}
	UCameraComponent* GetFirstPersonCameraComponment()const{return  FirstPersonCameraComponent;}

	UFUNCTION()
	void Fire();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
};
