#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	std::cout << "modbrain has started!" << std::endl;

	sf::RenderWindow window(sf::VideoMode(512, 512), "modbrain");
	window.setFramerateLimit(60);

	sf::CircleShape shape(128.0f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(256, 256);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
