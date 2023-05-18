// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if(!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		CollisionComponent -> BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		CollisionComponent -> OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);

		CollisionComponent -> InitSphereRadius(15.0f);

		RootComponent=CollisionComponent;
	}
	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent -> SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent -> InitialSpeed = 3000.0f;
		ProjectileMovementComponent -> MaxSpeed = 3000.0f;
		ProjectileMovementComponent -> bRotationFollowsVelocity = true;
		ProjectileMovementComponent -> bShouldBounce = true;
		ProjectileMovementComponent -> Bounciness = 0.3f;
		ProjectileMovementComponent -> ProjectileGravityScale= 0.0f;
	}
	if(!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent -> SetStaticMesh(Mesh.Object);
		}
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Materials/SphereMat.SphereMat'"));
		if (Material.Succeeded())
		{
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent -> SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent -> SetRelativeScale3D(FVector(0.09F,0.09F,0.09F));
		ProjectileMeshComponent -> SetupAttachment(RootComponent);
	}
	InitialLifeSpan=3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent -> Velocity = ShootDirection * ProjectileMovementComponent -> InitialSpeed;
}
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor!=this&&OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	Destroy();
}


