#include "AssetManager.h"

void Engine::AssetManager::loadTexture(std::string name, std::string fileName)
{
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(fileName))
	{
		m_textures[name] = std::move(texture);
	}
	else
		std::cout << "Failed to load texture: " << fileName << std::endl;
}

sf::Texture& Engine::AssetManager::getTexture(std::string name)
{
	return *(m_textures.at(name).get());
}

void Engine::AssetManager::loadFont(std::string name, std::string fileName)
{
	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
	if (font->loadFromFile(fileName))
	{
		this->m_fonts[name] = std::move(font);
	}
	else
		std::cout << "Failed to load font: " << fileName << std::endl;
}

sf::Font& Engine::AssetManager::getFont(std::string name)
{
	return *(m_fonts.at(name).get());
}