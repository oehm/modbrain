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
	for each (std::pair<Node*, float*> input in _inputs)
	{
		input.first->AddToLevel(*input.second);
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
		*output.second = output.first->GetLevel();
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

Node * Module::AddInput(Node * node, float * data)
{
	_inputs.push_back(std::make_pair(node, data));
	return node;
}

Node * Module::AddOutput(Node * node, float * data)
{
	_outputs.push_back(std::make_pair(node, data));
	return node;
}

//sf::Sprite Module::Draw()
//{
//	sf::RenderTexture renderTexture;
//	if (!renderTexture.create(500, 500))
//	{
//		std::cout << "sfml has failed" << std::endl;
//
//		// error...
//	}
//
//	renderTexture.clear();
//
//
//	sf::CircleShape shape(16.0f);
//	shape.setFillColor(sf::Color::White);
//	shape.setOutlineColor(sf::Color::Blue);
//	shape.setOutlineThickness(0.2f);
//
//	renderTexture.draw(shape);
//
//	renderTexture.display();
//
//	const sf::Texture& texture = renderTexture.getTexture();
//	sf::Sprite sprite(texture);
//	return sprite;
//}

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
