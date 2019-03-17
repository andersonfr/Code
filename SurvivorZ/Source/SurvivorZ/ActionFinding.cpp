// Fill out your copyright notice in the Description page of Project Settings.

#define MAXITERATIONS 1000

#include "ActionFinding.h"
#include "Heap.h"

void ActionFinding::Planning(WorldState & startState, const TArray<Action*> actions, Node & outNode)
{
	TSet<Node> closedSet;
	Heap openSet = Heap();
	Node startNode = Node(startState);

	openSet.Insert(startNode);
	int32 cnt = 0;

	while(openSet.Count() > 0 && cnt < MAXITERATIONS) {
		Node current = openSet.GetMin();
		openSet.DeleteMin();

		closedSet.Emplace(current);
		if (current.world.IsGoal()) {
			outNode = current;
			return;
		}
		TArray<WorldState> worldStates;
		GetAvailableNodes(current.world, actions, worldStates);

		for (auto& ws : worldStates) {
			//Defining new Node
			Node nNode = Node(ws);
			int32 cost = nNode.gCost + ws.action->cost;
			
			if (MemberInClose(nNode, closedSet))
				continue;

			if (cost < nNode.gCost || !openSet.Contains(nNode)) 
			{
				nNode.gCost = cost;
				nNode.hCost = ws.CalculateHeuristic();
				nNode.SetFcost();
				nNode.parent = &current;

				if (!openSet.Contains(nNode))
					openSet.Insert(nNode);
				else {
					openSet.UpdateItem(nNode);
				}
			}
		}
	}

}

void ActionFinding::GetAvailableNodes(WorldState & current, const TArray<Action*> actions, TArray<WorldState>& outWorldState)
{
	TArray<EGoal> conditionsToFullfil = current.GetGoalKeyList();
	
	for (auto& condGoal : conditionsToFullfil) {
		for (auto& action : actions) {
			if (action->effects.Contains(condGoal)) {
				//updating current world state
				TPair<bool, bool> temp;
				temp.Key = current.GetKeyValue(condGoal).Value;
				temp.Value = current.GetKeyValue(condGoal).Value;
				//current.AddPreCondition(condGoal, temp);

				WorldState nWS(current);
				nWS.AddPreCondition(condGoal,temp);
				for (auto& pre : action->preConditions) {
					if (pre.Key != EGoal::KNone)
						nWS.AddPreCondition(pre.Key, TPair<bool, bool>(!pre.Value, pre.Value));
				}
				
				nWS.action = action;
				outWorldState.Emplace(nWS);
			}
		}
	}
}

bool ActionFinding::MemberInClose(const Node & node, const TSet<Node> & closeSet)
{
	bool result = false;
	for (auto& n : closeSet) 
	{
		if (n.world == node.world) {
			result = true;
			break;
		}
	}
	return result;
}
