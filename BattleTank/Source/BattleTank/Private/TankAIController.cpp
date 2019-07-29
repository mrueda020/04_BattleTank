// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
// Depends on movement component via pathfinding system
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: %s can't find player tank"),*ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: %s found player: %s"),*ControlledTank->GetName(), *(PlayerTank->GetName()));
	}
}


void ATankAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(PlayerTank)) {
		
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim towards the player

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//ControlledTank->Fire();


	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); //Return Possesed Tank by the AI
} 

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; } // Note the !, very important
	return Cast<ATank>(PlayerPawn);
} 