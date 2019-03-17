// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EGoal {
	KNone,
	KWander,
	KKillenemy
};

/**
 * 
 */
class SURVIVORZ_API WorldState
{
public:
	class Action* action;

public:
	WorldState();
	WorldState(const EGoal goal, bool value);
	WorldState(const TMap<EGoal, TPair<bool, bool>>& _state);
	~WorldState();
private:
	/*State is formed by a goal and this current value and desired value
	A world state only will be fullfiled when all of its current values are equals to their desired values*/
	TMap<EGoal, TPair<bool, bool>> state;
public:
	void AddPreCondition(const EGoal key, TPair<bool, bool> value);
	TArray<EGoal> GetGoalKeyList();
	TPair<bool, bool> GetKeyValue(EGoal key);
	int32 CalculateHeuristic();
	bool IsGoal();
	bool operator ==(const WorldState& other) const;
};
