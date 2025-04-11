#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <stack>
#include <map>
#include <string>

#include "StateMachine.h"
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace Engine { 

	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}
		void loadTexture(std::string name, std::string fileName);
		sf::Texture& getTexture(std::string name);
		void loadFont(std::string name, std::string fileName);
		sf::Font& getFont(std::string name);

	private:
		std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
		std::map<std::string, std::unique_ptr<sf::Font>> m_fonts;
	};

}