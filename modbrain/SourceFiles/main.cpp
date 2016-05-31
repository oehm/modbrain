#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Module.h"


std::vector<Node*> AddRandomNetwork(Module* module, int numberNodes, int numberEdges);

int main()
{
	std::cout << "modbrain has started!" << std::endl;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(512, 512), "modbrain", sf::Style::Resize, settings);
	window.setFramerateLimit(30);


	if (!Globals::font.loadFromFile("RobotoCondensed-Bold.ttf"))
	{
		std::cout << "could not load font!" << std::endl;

	}

	srand(time(NULL));

	bool pulse;
	Module module = Module(0.1f, 0.2f);

	Node* node = AddRandomNetwork(&module, 20, 60)[0];
	//module.AddInput(node, &pulse);



	sf::Color clearColor = sf::Color::White;
	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		/*std::cout << "press space to play Frame!" << std::endl;
		while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
		}*/

		window.clear(clearColor);

		module.OnUpdate();

		window.draw(module);

		window.display();

	}

	return 0;
}

std::vector<Node*> AddRandomNetwork(Module* module, int numberNodes, int numberEdges)
{
	std::vector<Node*> nodes;

	for (int i = 0; i < numberNodes; i++)
	{
		float threshold = (float)rand() / RAND_MAX;
		float level = 0.0f;//(float)rand() / RAND_MAX;
		nodes.push_back(module->AddNode(threshold, level));
	}

	for (int i = 0; i < numberEdges; i++)
	{
		int idx1 = rand() % nodes.size();
		int idx2 = rand() % nodes.size();
		float weight = (float)rand() / RAND_MAX;
		int delay = rand() % 10;//magic number: max delay

		module->AddEdge(nodes[idx1], nodes[idx2], weight, delay);
	}

	return nodes;
}