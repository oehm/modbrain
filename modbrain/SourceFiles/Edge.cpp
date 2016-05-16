#include "Edge.h"


void Edge::OnUpdate()
{
	if (_currentDelay == 0) {
		_targetNode->AddToLevel(_weigth);
	}
	_currentDelay -= 1;
} 

void Edge::OnFire()
{
	if (_currentDelay > 0) {
		_currentDelay = _currentDelay / 2;
	}
	else
	{
		_currentDelay = _delay;
	}
}

Edge::Edge(Node* targetNode, float weigth, int delay, int currentDelay) :
	_targetNode(targetNode),
	_weigth(weigth),
	_delay(delay),
	_currentDelay(currentDelay)
{
}


Edge::~Edge()
{
}
