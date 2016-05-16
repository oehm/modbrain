#pragma once
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Edge.h"

//forward declarations:
class Node;
class Edge;

class Module
{
private:
	float _abstraction;
	float _signalStrength;

	std::vector<Node*> _nodes;
	std::vector<Edge*> _edges;

	std::vector<std::pair<Node*, float*>> _inputs;
	std::vector<std::pair<Node*, float* >> _outputs;


public:

	float GetAbstraction();
	float GetSignalStrength();

	Node* AddNode(float threshold = 0.5f, float level = 0.0f);
	Edge* AddEdge(Node* fromNode, Node* targetNode, float weigth, int delay, int currentDelay);
	Node* AddInput(Node* node, float* data);
	Node* AddOutput(Node* node, float* data);

	void OnUpdate();

	Module(float abstraction = 0.1f, float signalStrength = 0.1f);

	~Module();
};