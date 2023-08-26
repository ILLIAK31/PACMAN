#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Pacman.hpp"
#include <string>
//
#include <iostream>

Game::Game(Menu menu):Window(sf::VideoMode(CELL*Width*Screen, CELL*Height*Screen), "Pacman"),matrix(Width, std::vector<std::string>(Height)),pacman(matrix)
{
	Icon.loadFromFile("Icon.png");
	Window.setIcon(48, 48, Icon.getPixelsPtr());
	Window.setFramerateLimit(10);

	while (!menu.Get_Menu_End())
		menu.Update(Window);

	if (!Pacman_Texture.loadFromFile("pacman_body.png")) {}
	Pacman_Sprite.setTexture(Pacman_Texture);
	float Pacman_Scale = 0.085f;
	Pacman_Sprite.setScale(Pacman_Scale, Pacman_Scale);

	matrix[4][10] = "score1";
	matrix[4][25] = "score2";
	matrix[38][35] = "fruit1";

	if (!Score1_Texture.loadFromFile("score1.png")) {}
	Score1_Sprite.setTexture(Score1_Texture);
	float Score1_Scale = 0.075f , Score2_Scale = 0.19f , fruit1_Scale = 0.04f;
	Score1_Sprite.setScale(Score1_Scale, Score1_Scale);

	if (!Score2_Texture.loadFromFile("score2.png")) {}
	Score2_Sprite.setTexture(Score2_Texture);
	Score2_Sprite.setScale(Score2_Scale, Score2_Scale);

	if (!fruit1_Texture.loadFromFile("fruit1.png")) {}
	fruit1_Sprite.setTexture(fruit1_Texture);
	fruit1_Sprite.setScale(fruit1_Scale, fruit1_Scale);

	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
			if (height == 5 && width >= 0 && width <= 42)
				matrix[height][width] = "#";
	}
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
			if (height > 5 && (width == 0 || width == 41) && height <= 35)
				matrix[height][width] = "#";
	}
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
			if (height == 36 && width >= 0 && width <= 42)
				matrix[height][width] = "#";
	}
	
	matrix[9][4] = matrix[9][5] = matrix[9][6] = matrix[9][7] = matrix[9][8] = matrix[10][4] = matrix[11][4] = matrix[11][5] = matrix[11][6] = matrix[11][7] = matrix[11][8] = matrix[10][8] = "#";
	
	matrix[6][20] = matrix[7][20] = matrix[8][20] = matrix[9][20] = matrix[10][20] = matrix[11][20] = matrix[6][21] = matrix[7][21] = matrix[8][21] = matrix[9][21] = matrix[10][21] = matrix[11][21] = "#";

	matrix[9][12] = matrix[9][13] = matrix[9][14] = matrix[9][15] = matrix[9][16]  = matrix[10][12] = matrix[10][16] = matrix[11][12] = matrix[11][13] = matrix[11][14] = matrix[11][15] = matrix[11][16] = "#";

	matrix[15][4] = matrix[15][5] = matrix[15][6] = matrix[15][7] = matrix[15][8] = matrix[16][4] = matrix[16][5] = matrix[16][6] = matrix[16][7] = matrix[16][8] = "#";

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
	Window.setSize(sf::Vector2u(CELL * Width * Screen, CELL * Height * Screen));
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * Width, CELL * Height)));
	sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));
	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
		{
			if (matrix[height][width] == "#")
			{
				cell.setFillColor(sf::Color::Red);
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
				fruit1_Sprite.setPosition(width*CELL, height*CELL);
				Window.draw(fruit1_Sprite);
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