// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Heap.h"
#include "WorldState.h"
#include "Action.h"

/**
 * 
 */

class SURVIVORZ_API ActionFinding 
{
	
public:
	static void Planning(WorldState& startState,  const TArray<Action*> actions, Node& outNode);
	static void WorldStates(WorldState& current, const TArray<Action*> actions, TArray<WorldState>& outWorldState);

private:
	static bool MemberInClose(const Node& node, const TSet<Node> & closeSet );
	
};
