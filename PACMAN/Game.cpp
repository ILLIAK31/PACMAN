#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Pacman.hpp"
//
#include <iostream>

Game::Game():Window(sf::VideoMode(CELL*Width*Screen, CELL*Height*Screen), "Pacman"),matrix(Width, std::vector<unsigned char>(Height)),pacman(matrix)
{
	Icon.loadFromFile("Icon.png");
	Window.setIcon(48, 48, Icon.getPixelsPtr());
	Window.setFramerateLimit(10);
	if (!Pacman_Texture.loadFromFile("pacman_body.png")) {}
	Pacman_Sprite.setTexture(Pacman_Texture);
	float Pacman_Scale = 0.085f;
	Pacman_Sprite.setScale(Pacman_Scale, Pacman_Scale);
	matrix[4][10] = '1';
	if (!Score1_Texture.loadFromFile("score1.png")) {}
	Score1_Sprite.setTexture(Score1_Texture);
	float Score1_Scale = 0.075f;
	Score1_Sprite.setScale(Score1_Scale, Score1_Scale);
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
			if (height == 5 && width >= 0 && width <= 42)
				matrix[height][width] = '#';
	}
}

void Game::Run()
{
	while (Window.isOpen())
	{
		Render();
	}
}

void Game::Render()
{
	Window.clear();
	Window.setSize(sf::Vector2u(CELL * Width * Screen, CELL * Height * Screen));
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * Width, CELL * Height)));
	sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
		{
			if (matrix[height][width] == '#')
			{
				cell.setFillColor(sf::Color::Red);
				cell.setPosition(CELL*width,CELL*height);
				Window.draw(cell);
			}
			else if (matrix[height][width] == '@')
			{
				Pacman_Sprite.setPosition(pacman.Get_X(), pacman.Get_Y());
				Window.draw(Pacman_Sprite);
				pacman.Get_X() += 2;
			}
			else if (matrix[height][width] == '1')
			{
				Score1_Sprite.setPosition(width,height);
				Window.draw(Score1_Sprite);
			}
		}
	}
	Window.display();
}

void Game::Update()
{
	//
}

void Game::Process()
{
	//
}

Game::~Game(){}