#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Module.h"
#include "Edge.h"

// forward declarations:
class Edge;
class Module;

class Node : public sf::Drawable, public sf::Transformable // rework to split visual part from logic part
{
public:

	Module* _parentModule;
	float _threshold;
	float _level;
	std::vector<Edge*> _edges;

	float radius = 16.0f;

	void OnUpdate();

	void AddToLevel(float level);

	Edge* AddEdge(Edge* edge);

	Node(Module* parentModule, float threshold = 0.5f, float level = 0.0f);

	~Node();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

