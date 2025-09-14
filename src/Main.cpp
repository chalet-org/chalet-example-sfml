#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	// If needed
	// float screenScale = platform.getScreenScalingFactor(window.getSystemHandle());

	sf::Vector2u resolution { 640, 480 };
	sf::VideoMode mode(resolution);

	sf::ContextSettings settings;
#if !defined(SFML_SYSTEM_MACOS)
// settings.majorVersion = 4;
// settings.minorVersion = 1;
// settings.depthBits = 24;
// settings.stencilBits = 8;
// settings.attributeFlags = sf::ContextSettings::Attribute::Core;
#endif
	sf::RenderWindow window(mode, "SFML works!", sf::State::Windowed, settings);
	platform.initialize(window.getNativeHandle());

	// Center the window manually
	auto desktopMode = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktopMode.size.x / 2 - resolution.x / 2, desktopMode.size.y / 2 - resolution.y / 2));

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
	shape.setPosition(sf::Vector2f {
		static_cast<float>(mode.size.x / 2) - shape.getRadius(),
		static_cast<float>(mode.size.y / 2) - shape.getRadius(),
	});

	shape.setTexture(shapeTexture.get());

	sf::Color clearColor { 100, 149, 237 };

	window.setFramerateLimit(30);
	window.clear(clearColor);
	window.display();

	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(clearColor);
		window.draw(shape);
		window.display();
	}

	return EXIT_SUCCESS;
}
