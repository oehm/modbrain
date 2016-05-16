#include "Node.h"


void Node::OnUpdate()
{
	if (_level >= _threshold) {
		for each (Edge* edge in _edges)
		{
			edge->OnFire();
			_level = 0.0f;
		}
	}
	_level -= _level * _parentModule->GetAbstraction();
}

void Node::AddToLevel(float level)
{
	_level += level * _parentModule->GetSignalStrength();
	if (_level > 1.0f) _level = 1.0f;
	if (_level < -1.0f) _level = -1.0f;
}

Edge * Node::AddEdge(Edge* edge)
{
	_edges.push_back(edge);
	return edge;
}

float Node::GetLevel()
{
	return _level;
}

Node::Node(Module* parentModule, float threshold, float level ):
	_parentModule(parentModule),
	_threshold(threshold),
	_level(level)
{
	
}

Node::~Node()
{
}
