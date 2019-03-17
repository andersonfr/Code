// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
/**
 * 
 */

class SURVIVORZ_API Action
{
public:
	TMap<EGoal, bool> preConditions;
	TMap<EGoal, bool> effects;
	FName actionName;
	int32 cost;

protected:
	bool isDone;
	float range;
public:	
	Action(const FName, int32);
	~Action();

public:
	virtual bool IsInRange(FVector location) = 0;
	virtual void Perform() = 0;
	virtual bool IsDone() = 0;
	virtual bool CheckProceduralPreCondition(UObject* agent) = 0;
};
