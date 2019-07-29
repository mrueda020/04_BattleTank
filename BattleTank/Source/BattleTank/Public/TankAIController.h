// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private :
	virtual void BeginPlay() override;

	
	
	virtual void Tick(float DeltaTime) override;
	//How close can the AI get 
	float AcceptanceRadius = 3000;
};
