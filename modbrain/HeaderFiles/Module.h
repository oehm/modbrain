#pragma once
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Edge.h"

//forward declarations:
class Node;
class Edge;

class Module : public sf::Drawable, public sf::Transformable // rework to split visual part from logic part
{
public:
	float _abstraction;
	float _signalStrength;

	std::vector<Node*> _nodes;
	std::vector<Edge*> _edges;

	std::vector<std::pair<Node*, bool*>> _inputs;
	std::vector<std::pair<Node*, bool* >> _outputs;

	float GetAbstraction();
	float GetSignalStrength();

	Node* AddNode(float threshold = 0.5f, float level = 0.0f);
	Edge* AddEdge(Node* fromNode, Node* targetNode, float weigth = 0.5f, int delay = 1, int currentDelay = -1);
	Node* AddInput(Node* node, bool* pulse);
	Node* AddOutput(Node* node, float* data);

	void OnUpdate();

	Module(float abstraction = 0.1f, float signalStrength = 0.1f);

	~Module();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};