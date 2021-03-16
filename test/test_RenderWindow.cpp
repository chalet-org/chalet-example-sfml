#include <catch2/catch.hpp>

// This example is a bit silly, but you get the idea
TEST_CASE("sf::RenderWindow", "[renderwindow]") {
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	REQUIRE(window.getSize().x == 200);
	REQUIRE(window.getSize().y == 200);

	sf::CircleShape shape(window.getSize().x/2);
	shape.setFillColor(sf::Color::White);

	REQUIRE(shape.getRadius() == 100.0f);
	REQUIRE(shape.getFillColor() == sf::Color::White);
	REQUIRE(static_cast<int>(shape.getLocalBounds().width) == 198); // 🤔
	REQUIRE(static_cast<int>(shape.getLocalBounds().height) == 200);

	sf::Texture shapeTexture;
	shapeTexture.loadFromFile("content/sfml.png");
	shape.setTexture(&shapeTexture);

	REQUIRE(shapeTexture.getSize().x == 256);
	REQUIRE(shapeTexture.getSize().y == 256);
	REQUIRE(shape.getTexture() == &shapeTexture);

	// Show the RenderWindow once
	window.clear();
	window.draw(shape);
	window.display();

	REQUIRE(window.isOpen() == true);

}