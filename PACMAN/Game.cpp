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

	float Score1_Scale = 0.075f, Score2_Scale = 0.19f, PM_Scale = 0.065f , Wall_Scale = 0.055f;

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

	if (!Wall1_Texture.loadFromFile("1.png")) {}
	Wall1_Sprite.setTexture(Wall1_Texture);
	Wall1_Sprite.setScale(0.035f, 0.055f);

	if (!Wall2_Texture.loadFromFile("2.png")) {}
	Wall2_Sprite.setTexture(Wall2_Texture);
	Wall2_Sprite.setScale(0.055f, 0.075f);

	if (!Wall3_Texture.loadFromFile("3.png")) {}
	Wall3_Sprite.setTexture(Wall3_Texture);
	Wall3_Sprite.setScale(0.055f, 0.055f);

	if (!Wall4_Texture.loadFromFile("4.png")) {}
	Wall4_Sprite.setTexture(Wall4_Texture);
	Wall4_Sprite.setScale(0.060f, 0.070f);

	if (!Wall5_Texture.loadFromFile("5.png")) {}
	Wall5_Sprite.setTexture(Wall5_Texture);
	Wall5_Sprite.setScale(0.025f, 0.035f);

	if (!Wall6_Texture.loadFromFile("6.png")) {}
	Wall6_Sprite.setTexture(Wall6_Texture);
	Wall6_Sprite.setScale(0.065f, 0.050f);

	if (!Wall7_Texture.loadFromFile("7.png")) {}
	Wall7_Sprite.setTexture(Wall7_Texture);
	Wall7_Sprite.setScale(0.046f, 0.055f);

	/*if (!Wall8_Texture.loadFromFile("8.png")) {}
	Wall8_Sprite.setTexture(Wall8_Texture);
	Wall8_Sprite.setScale(0.055f, 0.055f);*/

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
			else if (matrix[height][width] == "#1")
			{
				Wall1_Sprite.setPosition(width*CELL, height*CELL);
				Window.draw(Wall1_Sprite);
			}
			else if (matrix[height][width] == "#2")
			{
				Wall2_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall2_Sprite);
			}
			else if (matrix[height][width] == "#3")
			{
				Wall3_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall3_Sprite);
			}
			else if (matrix[height][width] == "#4")
			{
				Wall4_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall4_Sprite);
			}
			else if (matrix[height][width] == "#5")
			{
				Wall5_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall5_Sprite);
			}
			else if (matrix[height][width] == "#6")
			{
				Wall6_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall6_Sprite);
			}
			else if (matrix[height][width] == "#7")
			{
				Wall7_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall7_Sprite);
			}
			else if (matrix[height][width] == "#8")
			{
				Wall8_Sprite.setPosition(width * CELL, height * CELL);
				Window.draw(Wall8_Sprite);
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