// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
/**
 * 
 */




class SURVIVORZ_API FSM
{
public:
	AAgent * owner;
	class State* currentState = NULL;

public:
	FSM(AAgent * owner);
	FSM();
	~FSM();
	void ChangeState(class State* newState);
	void Update();
};


class SURVIVORZ_API State
{
public:
	FSM* machine;
	State();
	State(FSM* machine);
	~State();

	virtual void Begin();
	virtual void Update();
	virtual void End();
};

class SURVIVORZ_API  Idle : public State 
{
public:
	Idle(FSM* _machine) : State(_machine) {}

	virtual void Begin() override;
	virtual void Update() override;
	virtual void End() override;
};

class SURVIVORZ_API  MoveState : public State
{
public:
	MoveState(FSM* _machine) : State(_machine) {}

	virtual void Begin() override;
	virtual void Update() override;
	virtual void End() override;
};