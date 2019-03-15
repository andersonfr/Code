// Fill out your copyright notice in the Description page of Project Settings.

#include "Heap.h"

Heap::Heap(int capacity)
{

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
	int length = _vector.Num();
	int leftChildIndex = 2 * index + 1;
	int rightChildIndex = 2 * index + 2;

	if (leftChildIndex >= length)
		return;//leaf

	int min = index;

	if (_vector[index].index > _vector[leftChildIndex].index) {
		min = leftChildIndex;
	}

	if ((rightChildIndex < length) && (_vector[min].index > _vector[rightChildIndex].index)) {
		min = rightChildIndex;
	}

	if (min != index) {
		//swap
		Node temp = _vector[index];
		_vector[index] = _vector[min];
		_vector[min] = temp;
		BubbleDown(min);
	}

}

void Heap::BubbleUp(int index)
{
	if (index == 0)
		return;

	int parentIndex = (index - 1) / 2;

	if (_vector[parentIndex].index > _vector[index].index) {
		Node temp = _vector[parentIndex];
		_vector[parentIndex] = _vector[index];
		_vector[index] = temp;
		BubbleUp(parentIndex);
	}
}

void Heap::Heapfy()
{
	int length = _vector.Num();
	for (int32 i = 0; i < length; i++)
	{
		BubbleDown(i);
	}
}

void Heap::Insert(Node node)
{
	_vector.Emplace(node);
	BubbleUp(_vector.Num()-1);
}

Node Heap::GetMin()
{
	return _vector[0];
}

void Heap::DeleteMin()
{
	int length = _vector.Num();

	if (length == 0)
		return;

	_vector[0] = _vector[length - 1];
	_vector.Pop();

	BubbleDown(0);

}
