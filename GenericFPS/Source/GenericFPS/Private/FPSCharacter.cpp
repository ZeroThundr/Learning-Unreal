// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"



// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(55.f,96.0f);

	FirstPersonCameraComponent =  CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FirstPersonCameraComponent->bUsePawnControlRotation=true;

	Mesh1P=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow= false;
	Mesh1P -> CastShadow = false;

	Mesh1P->SetRelativeLocation(FVector(-30.f,0.f,-150.f));

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetOwnerNoSee(true);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
	check(GEngine != nullptr);

	//display message for 5 seconds that we are using the FPSCharacter class
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("We are using the FPSChar class."));
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this, &AFPSCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this, &AFPSCharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AFPSCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AFPSCharacter::Look);
		
	}
}
void AFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(),MovementVector.Y);
		AddMovementInput(GetActorRightVector(),MovementVector.X);
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("We are using the FPSChar class."));
		AddControllerPitchInput(LookAxisVector.Y);
		FString YValue = LookAxisVector.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *YValue));
	}
}




