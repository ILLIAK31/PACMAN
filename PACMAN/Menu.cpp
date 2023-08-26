#include <SFML/Graphics.hpp>
#include "Menu.hpp"

Menu::Menu()
{
	float Menu1_Scale = 0.070f , Menu2_Scale = 0.250f;
	
	if (!Menu1_Texture.loadFromFile("Menu1.png")) {}
	Menu1_Sprite.setTexture(Menu1_Texture);
	Menu1_Sprite.setScale(Menu1_Scale, Menu1_Scale);
	Menu1_Sprite.setPosition(35, 10);

	if (!Menu2_Texture.loadFromFile("Menu2.png")) {}
	Menu2_Sprite.setTexture(Menu2_Texture);
	Menu2_Sprite.setScale(Menu2_Scale, Menu2_Scale);
	Menu2_Sprite.setPosition(100, 160);
}

Menu::~Menu(){}

void Menu::Render(sf::RenderWindow& Window)
{
	Window.clear();
	Window.setSize(sf::Vector2u(CELL * Width * Screen, CELL * Height * Screen));
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * Width, CELL * Height)));
	Window.draw(Menu1_Sprite);
	Window.draw(Menu2_Sprite);
	Window.display();
}

void Menu::Update(sf::RenderWindow& Window)
{
	Render(Window);
	Process(Window);
}

void Menu::Process(sf::RenderWindow& Window)
{
	sf::Event Event;
	while (Window.pollEvent(Event))
		if (Event.type == sf::Event::Closed)
			Window.close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		Menu_End = true;
}

bool Menu::Get_Menu_End()
{
	return (Menu_End)?true:false;
}
