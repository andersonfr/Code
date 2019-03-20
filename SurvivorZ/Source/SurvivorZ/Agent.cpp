// Fill out your copyright notice in the Description page of Project Settings.

#include "Agent.h"
#include "FSM.h"

// Sets default values
AAgent::AAgent()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	//We instantiate the state machine
	fsmShared = MakeShareable(new FSM(this));
	Idle* idleState = new Idle(fsmShared.Get());
	fsmShared->ChangeState(idleState);
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

