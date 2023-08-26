#pragma once
#include <array>
#include <chrono>
#include "Pacman.hpp"
#include "Menu.hpp"

constexpr unsigned char CELL = 8;
constexpr unsigned char Height = 42;
constexpr unsigned char Width = 42;
constexpr unsigned char Screen = 2;

//constexpr unsigned char Frame_Duration = 16667;

class Game
{
	friend class Menu;
public:
	Game(Menu menu);
	void Run();
	~Game();
private:
	sf::RenderWindow Window;
	sf::Image Icon;
	void Render();
	void Update();
	void Process();
	std::vector<std::vector<std::string>> matrix;
	sf::Texture Pacman_Texture , Score1_Texture , Score2_Texture , fruit1_Texture;
	sf::Sprite Pacman_Sprite , Score1_Sprite , Score2_Sprite , fruit1_Sprite;
	Pacman pacman;
	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::milliseconds duration, duration0{ 0 };
	int speed{1};
};