// Fill out your copyright notice in the Description page of Project Settings.

#include "FSM.h"

FSM::FSM(AAgent* owner)
{
	this->owner = owner;
}

FSM::FSM()
{
}

FSM::~FSM()
{

}

void FSM::ChangeState(State* newState)
{
	if (currentState == nullptr) 
	{
		currentState = newState;
	}
	else
	{
		currentState->End();
		currentState = newState;
	}
	currentState->Begin();
}



void FSM::Update()
{
	currentState->Update();
}


State::State()
{
}

State::State(FSM* machine)
{
	this->machine = machine;
}

State::~State() 
{
}

void State::Begin()
{
	
}

void State::Update()
{
}

void State::End()
{
}

void Idle::Begin()
{
	UE_LOG(LogTemp,Warning,TEXT("Idle Begin"))
    this->machine->ChangeState(new MoveState(this->machine));
}

void Idle::Update()
{
}

void Idle::End()
{
	UE_LOG(LogTemp, Warning, TEXT("Deleting Idle"))
	delete this->machine;
	delete this;
}

void MoveState::Begin()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Begin"))
		if (this->machine != nullptr) 
		{
			UE_LOG(LogTemp, Warning, TEXT("machine still ok"))
		}
}

void MoveState::Update()
{
}

void MoveState::End()
{
	UE_LOG(LogTemp, Warning, TEXT("Deleting Move"))
    delete this->machine;
	delete this;
}
