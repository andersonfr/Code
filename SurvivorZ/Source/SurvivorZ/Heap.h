// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldState.h"
/**
 * 
 */

struct Node {
	int32 ID;
	Node(int32 _index) : heapIndex(_index) {}
	Node() {}
	
	Node(const WorldState& state) :world(state) {}

	int32 gCost;
	int32 hCost;
	int32 fCost;

	WorldState world;

	Node* parent;
	int32 heapIndex;

	void SetFcost() 
	{
		fCost = gCost + hCost;
	}

	friend uint32 GetTypeHash(const Node& Other)
	{
		return GetTypeHash(Other.ID);
	}

	inline bool operator == (const Node& Other) const
	{
		return ID == Other.ID;
	}

	//comparing priorites a<b means a has a lower priority than b.
	inline bool operator < ( const Node& rhs) const {
		int32 compare = CompareTo(fCost, rhs.fCost);
		if (compare == 0) {
			compare = CompareTo(hCost, rhs.hCost);
		}
		//we want return true if a.fcost > b.fcost
		return compare > 0;
	}
	//comparing priorites a>b means a has a higher priority than b.
	inline bool operator > (const Node& rhs) const {
		int32 compare = CompareTo(fCost, rhs.fCost);
		if (compare == 0) {
			compare = CompareTo(hCost, rhs.hCost);
		}
		//we want return true if a.fcost < b.fcost
		//compare = compare * -1;
		return compare < 0;
	}


	inline int32 CompareTo(const float& v1, const float& v2) const {
		if (v1 < v2) return -1;
		else if (v1 == v2) return 0;
		else return 1;
	}

};


class SURVIVORZ_API Heap
{
	
public:
	Heap(int capacity);
	Heap(const TArray<Node>& vector);
	Heap();
	~Heap();
private:
	TArray<Node> _vector;
	
public:
	int32 items;

private:
	void BubbleDown(int index);
	void BubbleUp(int index);
	void Heapfy();

public:
	void Insert(Node& node);
	Node GetMin();
	void DeleteMin();
	inline int32 Count() const {
		return items;
	}
	inline bool Contains(const Node& otherNode) {
		int32 index = 0;
		return Find(otherNode) != nullptr;
	}
	void UpdateItem(const Node& node);

private:
	inline Node* Find(const Node& otherNode) {
		return _vector.FindByPredicate([&](const Node& n) {return n.world == otherNode.world; });
	}
};
