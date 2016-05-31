#include <iostream>
#include "Node.h"
#include "Globals.h"


void Node::OnUpdate()
{
	if (_level >= _threshold) {

		for each (Edge* edge in _edges)
		{
			edge->OnFire();
		}

		_level = 0.0f;
	}
	_level -= _level * _parentModule->_abstraction;
	if (abs(_level) < 0.0001) _level = 0.0f;
}

void Node::AddToLevel(float level)
{
	_level += level * _parentModule->_signalStrength;
	if (_level > 1.0f) _level = 1.0f;
	if (_level < -1.0f) _level = -1.0f;
}

Edge * Node::AddEdge(Edge* edge)
{
	_edges.push_back(edge);
	return edge;
}

Node::Node(Module* parentModule, float threshold, float level) :
	_parentModule(parentModule),
	_threshold(threshold),
	_level(level)
{
	std::cout << "created node with: _threshold: " << _threshold << " _level: " << _level << std::endl;
}

Node::~Node()
{
}

void Node::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::CircleShape shape(radius);
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1.5f);
	shape.setOrigin(radius, radius);
	shape.setPosition(getPosition());

	sf::Text textLevel;
	textLevel.setFont(Globals::font);
	textLevel.setString(std::to_string((int)(_level * 100.0f)));
	textLevel.setCharacterSize(14);
	textLevel.setPosition(getPosition() - sf::Vector2f(7.0f, 14.0f));

	sf::Text textThresh;
	textThresh.setFont(Globals::font);
	textThresh.setString(std::to_string((int)(_threshold * 100.0f)));
	textThresh.setCharacterSize(14);
	textThresh.setPosition(getPosition() - sf::Vector2f(7.0f, 0.0f));

	target.draw(shape, states);
	target.draw(textLevel, states);
	target.draw(textThresh, states);
}
