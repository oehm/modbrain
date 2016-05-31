#pragma once
#include "Node.h"

//forward declarations:
class Node;

class Edge
{
public:

	Node* _targetNode;
	float _weigth;
	int _delay;
	int _currentDelay;


	Node* GetTargetNode();

	void OnUpdate();

	void OnFire();

	Edge(Node* targetNode, float weigth = 0.1f, int delay = 0, int currentDelay = -1);

	~Edge();
};

