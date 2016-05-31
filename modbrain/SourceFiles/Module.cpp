#include <iostream>
#include "Module.h"

float Module::GetAbstraction()
{
	return _abstraction;
}

float Module::GetSignalStrength()
{
	return _signalStrength;
}

void Module::OnUpdate()
{
	for each (std::pair<Node*, bool*> input in _inputs)
	{
		if (*input.second)
		{
			input.first->_level = input.first->_threshold;
		}
	}

	for each (Node* node in _nodes)
	{
		node->OnUpdate();
	}

	for each (Edge* edge in _edges)
	{
		edge->OnUpdate();
	}

	for each (std::pair<Node*, float*> output in _outputs)
	{
		*output.second = output.first->_level;
	}
}

Node* Module::AddNode(float threshold, float level)
{
	Node* node = new Node(this, threshold, level);
	_nodes.push_back(node);
	return node;
}

Edge * Module::AddEdge(Node * fromNode, Node * targetNode, float weigth, int delay, int currentDelay)
{
	if (std::find(_nodes.begin(), _nodes.end(), fromNode) == _nodes.end() ||
		std::find(_nodes.begin(), _nodes.end(), targetNode) == _nodes.end()) {
		return nullptr;
	}
	else
	{
		Edge* edge = new Edge(targetNode, weigth, delay, currentDelay);
		fromNode->AddEdge(edge);
		_edges.push_back(edge);
		return edge;
	}
}

Node * Module::AddInput(Node * node, bool * pulse)
{
	_inputs.push_back(std::make_pair(node, pulse));
	return node;
}

Node * Module::AddOutput(Node * node, float * data)
{
	_outputs.push_back(std::make_pair(node, data));
	return node;
}

Module::Module(float abstraction, float signalStrength) :
	_abstraction(abstraction),
	_signalStrength(signalStrength)
{
}


Module::~Module()
{
	for each (Edge* edge in _edges)
	{
		delete edge;
	}

	for each (Node* node in _nodes)
	{
		delete node;
	}
}

void Module::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	float seg = 2 * 3.1415926535 / _nodes.size();
	sf::Vector2f center(256.0f, 256.0f);

	for (int i = 0; i < _nodes.size(); i++)
	{
		Node* node = _nodes[i];

		for (int j = 0; j < node->_edges.size(); j++)
		{
			Edge* edge = node->_edges[j];

			sf::Vector2f originPosition = node->getPosition();
			sf::Vector2f targetPosition = originPosition - edge->GetTargetNode()->getPosition();
			targetPosition = targetPosition / sqrt(targetPosition.x * targetPosition.x + targetPosition.y * targetPosition.y);
			targetPosition = edge->GetTargetNode()->getPosition() + targetPosition * edge->GetTargetNode()->radius;

			//create diagramm of this value!!! moredimensional would be nice
			//std::cout << edge->_currentDelay << std::endl;
			if (edge->_currentDelay > 0) 
			{
				std::cout << edge->_currentDelay << std::endl;
			}
			sf::Vertex line[] =
			{
				sf::Vertex(originPosition, edge->_currentDelay > 0 ? sf::Color::Red : sf::Color::Blue),
				sf::Vertex(targetPosition, edge->_currentDelay == 0 ? sf::Color::Black : sf::Color::Blue)
			};

			float radius = 4.0f;
			sf::CircleShape shape(radius);
			shape.setFillColor(sf::Color::Blue);
			shape.setOutlineColor(sf::Color::Black);
			shape.setOutlineThickness(1.5f);
			shape.setOrigin(radius, radius);
			shape.setPosition(targetPosition);

			target.draw(shape, states);
			target.draw(line, 2, sf::Lines, states);
		}
	}

	for (int i = 0; i < _nodes.size(); i++)
	{
		Node* node = _nodes[i];

		sf::Vector2f position = center;
		position.x += sin(seg*i) * 200.0f;
		position.y += cos(seg*i) * 200.0f;

		sf::Vector2f endAxon = center;
		endAxon.x += sin(seg*i) * 100.0f;
		endAxon.y += cos(seg*i) * 100.0f;

		node->setPosition(position);

		sf::Vertex line[] =
		{
			sf::Vertex(position),
			sf::Vertex(endAxon)
		};

		target.draw(*node, states);
	}

}
