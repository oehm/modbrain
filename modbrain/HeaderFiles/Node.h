#pragma once
#include <vector>
#include "Module.h"
#include "Edge.h"

// forward declarations:
class Edge;
class Module;

class Node
{
private:

	Module* _parentModule;
	float _threshold;
	float _level;
	std::vector<Edge*> _edges;

public:
	void OnUpdate();

	void AddToLevel(float level);

	Edge* AddEdge(Edge* edge);

	float GetLevel();

	Node(Module* parentModule, float threshold = 0.5f, float level = 0.0f);

	~Node();
};

