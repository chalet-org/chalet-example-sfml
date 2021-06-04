#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// Use the screenScalingFactor
	sf::VideoMode mode {
		static_cast<uint>(512.0f * screenScalingFactor),
		static_cast<uint>(512.0f * screenScalingFactor),
	};

	sf::ContextSettings inSettings;
#if !defined(SFML_OS_MACOS)
// inSettings.majorVersion = 4;
// inSettings.minorVersion = 1;
// inSettings.depthBits = 24;
// inSettings.stencilBits = 8;
// inSettings.attributeFlags = sf::ContextSettings::Attribute::Core;
#endif
	window.create(mode, "SFML works!", sf::Style::Default, inSettings);
	platform.setIcon(window.getSystemHandle());

	sf::ContextSettings settings = window.getSettings();
	std::cout << "OpenGL context created with version: "
			  << settings.majorVersion << "." << settings.minorVersion
			  << " with " << settings.depthBits << " depth bits, "
			  << settings.stencilBits << " stencil bits, "
			  << (settings.attributeFlags == sf::ContextSettings::Attribute::Core ? "Core Profile" : "Compatibility Profile")
			  << std::endl;

	sf::CircleShape shape(static_cast<float>(window.getSize().x / 2));
	shape.setFillColor(sf::Color::White);

	sf::Texture shapeTexture;
	shapeTexture.loadFromFile("content/sfml.png");
	shape.setTexture(&shapeTexture);

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
