// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent -> InitSphereRadius(40.f);
	SphereComponent -> SetCollisionProfileName(TEXT("Pawn"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentaion"));
	SphereVisual -> SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("'/Game/Sphere.Sphere'"));
	if(SphereVisualAsset.Succeeded())
	{
		SphereVisual -> SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual -> SetRelativeLocation(FVector(.0f,.0f,-40.0f));
		SphereVisual -> SetWorldScale3D(FVector(.8f));
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem -> SetupAttachment(SphereVisual);
	OurParticleSystem -> bAutoActivate = false;
	OurParticleSystem -> SetRelativeLocation(FVector(-20.f,.0f,20.f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("'/Game/ParticlesTUFFS.ParticlesTUFFS'"));
	if(ParticleAsset.Succeeded())
	{
		OurParticleSystem -> SetTemplate(ParticleAsset.Object);
	}
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm -> SetupAttachment(RootComponent);
	SpringArm -> SetRelativeRotation(FRotator(-45.f,0.f,0.f));
	SpringArm -> TargetArmLength = 400.f;
	SpringArm -> bEnableCameraLag = true;
	SpringArm -> CameraLagSpeed = 3.f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent -> UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

