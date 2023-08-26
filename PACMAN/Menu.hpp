#pragma once
#include "Game.hpp"

class Menu
{
	friend class Game;
public:
	Menu();
	~Menu();
	void Render(sf::RenderWindow& Window);
	void Update(sf::RenderWindow& Window);
	void Process(sf::RenderWindow& Window);
	bool Get_Menu_End();
private:
	sf::Texture Menu1_Texture , Menu2_Texture;
	sf::Sprite Menu1_Sprite , Menu2_Sprite;
	bool Menu_End{ false };
};