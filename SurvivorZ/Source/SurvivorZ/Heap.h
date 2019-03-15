// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct Node {
	int index;
	Node(int _index) : index(_index) {}
};


class SURVIVORZ_API Heap
{
	
public:
	Heap(int capacity);
	Heap(const TArray<Node>& vector);
	Heap();
	~Heap();
	TArray<Node> _vector;
	
private:
	void BubbleDown(int index);
	void BubbleUp(int index);
	void Heapfy();
public:
	void Insert(Node node);
	Node GetMin();
	void DeleteMin();
};
