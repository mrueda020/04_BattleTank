// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution){
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	}
	
}	// If no solution found do nothing

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet){
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection){
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I am here"));
	//Work-out difference between curretn barrel rotation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //forward vector i x vector
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel&&ProjectileBlueprint)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
