#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Pacman.hpp"
#include <string>
//
#include <iostream>

Game::Game(Menu menu):Window(sf::VideoMode(CELL*Width*Screen, CELL*Height*Screen*1.2), "Pacman"),matrix(Width, std::vector<std::string>(Height)),pacman(matrix)
{
	Icon.loadFromFile("Icon.png");
	Window.setSize(sf::Vector2u(CELL * Width * Screen, CELL * Height * Screen * 1.1));
	Window.setIcon(48, 48, Icon.getPixelsPtr());
	Window.setFramerateLimit(10);

	while (!menu.Get_Menu_End())
		menu.Update(Window);

	float Score1_Scale = 0.075f, Score2_Scale = 0.19f, PM_Scale = 0.065f;

	if (!Pacman_Texture.loadFromFile("pacman_body2.png")) {}
	Pacman_Sprite.setTexture(Pacman_Texture);
	float Pacman_Scale = 0.085f;
	Pacman_Sprite.setScale(Pacman_Scale, Pacman_Scale);

	if (!Score1_Texture.loadFromFile("score1.png")) {}
	Score1_Sprite.setTexture(Score1_Texture);
	Score1_Sprite.setScale(Score1_Scale, Score1_Scale);

	if (!Score2_Texture.loadFromFile("score2.png")) {}
	Score2_Sprite.setTexture(Score2_Texture);
	Score2_Sprite.setScale(Score2_Scale, Score2_Scale);

	if (!fruit1_Texture.loadFromFile("fruit1.png")) {}
	fruit1_Sprite.setTexture(fruit1_Texture);

	if (!PM1_Texture.loadFromFile("pacman_body.png")) {}
	PM1_Sprite.setTexture(PM1_Texture);
	PM1_Sprite.setScale(PM_Scale, PM_Scale);

	if (!PM2_Texture.loadFromFile("pacman_body.png")) {}
	PM2_Sprite.setTexture(PM2_Texture);
	PM2_Sprite.setScale(PM_Scale, PM_Scale);

	if (!PM3_Texture.loadFromFile("pacman_body.png")) {}
	PM3_Sprite.setTexture(PM3_Texture);
	PM3_Sprite.setScale(PM_Scale, PM_Scale);

	matrix_setup.Setup_Matrix(matrix);

	start = std::chrono::high_resolution_clock::now();
}

void Game::Run()
{
	while (Window.isOpen())
	{
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		if (duration.count() >= speed + duration0.count())
		{
			duration0 = duration;
			for (int i = 0; i < 10; ++i)
				Update();
		}
	}
}

void Game::Render()
{
	Window.clear();
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * Width, CELL * Height*1.1)));
	sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));
	sf::CircleShape cell2(1.5) , cell3(4);
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
		{
			if (matrix[height][width] == "#")
			{
				cell.setFillColor(sf::Color::Blue);
				cell.setPosition(CELL*width,CELL*height);
				Window.draw(cell);
			}
			else if (matrix[height][width] == "@")
			{
				Pacman_Sprite.setPosition(pacman.Get_X(), pacman.Get_Y());
				Window.draw(Pacman_Sprite);
			}
			else if (matrix[height][width] == "score1")
			{
				Score1_Sprite.setPosition(width,height);
				Window.draw(Score1_Sprite);
			}
			else if (matrix[height][width] == "score2")
			{
				Score2_Sprite.setPosition(width*CELL, height);
				Window.draw(Score2_Sprite);
			}
			else if (matrix[height][width] == "fruit1")
			{
				fruit1_Sprite.setPosition(width*CELL, height*CELL*1.11);
				fruit1_Sprite.setScale(fruit1_Scale, fruit1_Scale);
				Window.draw(fruit1_Sprite);
			}
			else if (matrix[height][width] == "PM1" && pacman.Get_Lifes() >= 1)
			{
				PM1_Sprite.setPosition(width * CELL, height * CELL * 1.11);
				Window.draw(PM1_Sprite);
			}
			else if (matrix[height][width] == "PM2" && pacman.Get_Lifes() >= 2)
			{
				PM2_Sprite.setPosition(width * CELL, height * CELL * 1.11);
				Window.draw(PM2_Sprite);
			}
			else if (matrix[height][width] == "PM3" && pacman.Get_Lifes() == 3)
			{
				PM3_Sprite.setPosition(width * CELL, height * CELL * 1.11);
				Window.draw(PM3_Sprite);
			}
			else if (matrix[height][width] == "*")
			{
				cell2.setFillColor(sf::Color::White);
				cell2.setPosition(CELL * width*1.013, CELL * height * 1.02);
				Window.draw(cell2);
			}
			else if (matrix[height][width] == "cherry")
			{
				fruit1_Sprite.setPosition(width * CELL, height * CELL*0.985);
				fruit1_Sprite.setScale(cherry_Scale, cherry_Scale);
				Window.draw(fruit1_Sprite);
			}
			else if (matrix[height][width] == "*P")
			{
				cell3.setFillColor(sf::Color::White);
				cell3.setPosition(CELL * width, CELL * height);
				Window.draw(cell3);
			}
		}
	}
	Window.display();
}

void Game::Update()
{
	pacman.Get_X() += 5;	
	Render();
}

void Game::Process()
{
	//
}

Game::~Game(){}