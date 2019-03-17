// Fill out your copyright notice in the Description page of Project Settings.

#include "Heap.h"

Heap::Heap(int capacity)
{
	_vector.SetNum(capacity);
}

Heap::Heap(const TArray<Node>& vector) : _vector(vector)
{
	Heapfy();
}

Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::BubbleDown(int index)
{
	int leftChildIndex = 2 * index + 1;
	int rightChildIndex = 2 * index + 2;

	int swapIndex;

	if (leftChildIndex < items){
		swapIndex = leftChildIndex;

		if (rightChildIndex < items) 
		{
			//does left child have a lower priority than right child?
			if (_vector[leftChildIndex] < _vector[rightChildIndex]){
				swapIndex = rightChildIndex;
			}
		}
		if (_vector[index] < _vector[swapIndex]) {
			Node tempnode = _vector[index];
			int32 tempIndex = tempnode.heapIndex;
			
			_vector[index] = _vector[swapIndex];
			_vector[swapIndex] = tempnode;

			_vector[index].heapIndex = _vector[swapIndex].heapIndex;
			_vector[swapIndex].heapIndex = tempIndex;
			
			BubbleDown(swapIndex);
		}
		else
			return;
	}
	else
		return;
}

void Heap::BubbleUp(int index)
{
	if (index == 0)
		return;

	int parentIndex = (index - 1) / 2;

	if (_vector[parentIndex] > _vector[index]) {
		Node tempnode = _vector[parentIndex];
		int32 tempIndex = tempnode.heapIndex;

		_vector[parentIndex] = _vector[index];
		_vector[index] = tempnode;
		
		_vector[parentIndex].heapIndex = _vector[index].heapIndex;
		_vector[index].heapIndex = tempIndex;

		BubbleUp(parentIndex);
	}
}

void Heap::Heapfy()
{
	//we bubble every node, starting from the root
	int length = _vector.Num();
	for (int32 i = 0; i < length; i++)
	{
		BubbleDown(i);
	}
}

void Heap::Insert(Node& node)
{
	//insert a new node to the end and then bubble it up 
	node.heapIndex = items;
	_vector.Emplace(node);
	BubbleUp(_vector.Num()-1);
	items++;
}

Node Heap::GetMin()
{
	return _vector[0];
}

void Heap::DeleteMin()
{
	//We remove the first, pick tha last one, put it at first and finnally bubble it down
	if (items == 0)
		return;

	items--;
	_vector[0] = _vector[items];
	_vector[0].heapIndex = 0;
	BubbleDown(0);
}

void Heap::UpdateItem(const Node & node)
{
	int32 index = 0;
	auto ptr = Find(node);
	if (ptr != nullptr) 
	{
		//we update the found node with aproppriate new values and the bubble it up
		ptr->parent = node.parent;
		ptr->gCost = node.gCost;
		ptr->hCost = node.hCost;
		ptr->world = node.world;
		ptr->fCost = node.fCost;
		
		BubbleUp(ptr->heapIndex);
	}
}
