#include "Platform/Platform.hpp"

void printContextSettingsFromWindow(const sf::ContextSettings& inSettings)
{
	std::cout << "OpenGL context created with version: "
			  << inSettings.majorVersion << "." << inSettings.minorVersion
			  << " with " << inSettings.depthBits << " depth bits, "
			  << inSettings.stencilBits << " stencil bits, "
			  << (inSettings.attributeFlags == sf::ContextSettings::Attribute::Core ? "Core Profile" : "Compatibility Profile")
			  << std::endl;
}

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScale = platform.getScreenScalingFactor(window.getSystemHandle());

	sf::VideoMode mode {
		static_cast<uint>(256.0f * screenScale),
		static_cast<uint>(256.0f * screenScale),
	};

	sf::ContextSettings settings;
#if !defined(SFML_SYSTEM_MACOS)
// settings.majorVersion = 4;
// settings.minorVersion = 1;
// settings.depthBits = 24;
// settings.stencilBits = 8;
// settings.attributeFlags = sf::ContextSettings::Attribute::Core;
#endif
	window.create(mode, "SFML works!", sf::Style::Default, settings);
	platform.setIcon(window.getSystemHandle());

	printContextSettingsFromWindow(window.getSettings());

	sf::CircleShape shape(static_cast<float>(window.getSize().x / 2));
	shape.setFillColor(sf::Color::White);

	auto shapeTexture = std::make_unique<sf::Texture>();
	if (!shapeTexture->loadFromFile("content/sfml.png"))
		return 1;

	shape.setTexture(shapeTexture.get());

	sf::Event event;

	window.clear();
	window.display();

	while (window.isOpen())
	{
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
