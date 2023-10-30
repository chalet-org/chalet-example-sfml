#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;

	// If needed
	// float screenScale = platform.getScreenScalingFactor(window.getSystemHandle());

	sf::Vector2u resolution{ 640, 480 };
	sf::VideoMode mode(resolution.x, resolution.y);

	sf::ContextSettings settings;
#if !defined(SFML_SYSTEM_MACOS)
// settings.majorVersion = 4;
// settings.minorVersion = 1;
// settings.depthBits = 24;
// settings.stencilBits = 8;
// settings.attributeFlags = sf::ContextSettings::Attribute::Core;
#endif
	window.create(mode, "SFML works!", sf::Style::Default, settings);
	platform.initialize(window.getSystemHandle());

	[](const sf::ContextSettings& inSettings) {
		std::cout << "OpenGL context created with version: "
				  << inSettings.majorVersion << "." << inSettings.minorVersion
				  << " with " << inSettings.depthBits << " depth bits, "
				  << inSettings.stencilBits << " stencil bits, "
				  << (inSettings.attributeFlags == sf::ContextSettings::Attribute::Core ? "Core Profile" : "Compatibility Profile")
				  << std::endl;
	}(window.getSettings());

	auto shapeTexture = std::make_unique<sf::Texture>();
	if (!shapeTexture->loadFromFile("content/sfml.png"))
		return EXIT_FAILURE;

	sf::CircleShape shape(static_cast<float>(shapeTexture->getSize().y) / 2.0f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(
		static_cast<float>(mode.width / 2) - shape.getRadius(),
		static_cast<float>(mode.height / 2) - shape.getRadius()
	);

	shape.setTexture(shapeTexture.get());

	sf::Event event;

	sf::Color clearColor{ 100, 149, 237 };

	window.setFramerateLimit(30);
	window.clear(clearColor);
	window.display();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(clearColor);
		window.draw(shape);
		window.display();
	}

	return EXIT_SUCCESS;
}
