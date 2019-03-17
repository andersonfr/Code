// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldState.h"

WorldState::WorldState()
{
}

WorldState::WorldState(const EGoal goal, bool value)
{
	TPair<bool,bool> kv;
	kv.Key = value;
	kv.Value = !value;
	state.Emplace(goal, kv);
}

WorldState::WorldState(const TMap<EGoal, TPair<bool, bool>>& _state) : state(_state)
{
}

WorldState::~WorldState()
{
}

void WorldState::AddPreCondition(const EGoal key, TPair<bool, bool> value)
{
	state.Emplace(key, value);
}

TArray<EGoal> WorldState::GetGoalKeyList()
{
	TArray<EGoal> temp;
	for (auto& item : state) {
		auto values = item.Value;
		bool result = values.Key != values.Value;
		
		if (result) temp.Emplace(item.Key);
	}
	return temp;
}

TPair<bool, bool> WorldState::GetKeyValue(EGoal key)
{
	return state[key];
}

int32 WorldState::CalculateHeuristic()
{
	int count = 0;
	for (const auto& conditions : state) 
	{
		TPair<bool, bool> vars = conditions.Value;
		if (vars.Key != vars.Value)
			count++;
	}
	return count;
}

bool WorldState::IsGoal()
{
	bool result = true;
	for (auto& c : state) 
	{
		TPair<bool, bool> vars = c.Value;
		result = vars.Value == vars.Key;
	}
	return result;
}

bool WorldState::operator==(const WorldState & other) const
{
	bool result = true;
	for (auto& kv : state)
	{
		if (other.state.Contains(kv.Key)) 
		{
			TPair<bool, bool> otherPair = other.state[kv.Key];
			TPair<bool, bool> myPair = state[kv.Key];
			result = (otherPair.Value == myPair.Value) && (otherPair.Key == myPair.Key);
		}
		else {
			return false;
		}
	}
	return result;
}
