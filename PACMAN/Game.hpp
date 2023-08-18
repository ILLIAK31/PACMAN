#pragma once
#include <array>
#include "Pacman.hpp"

constexpr unsigned char CELL = 8;
constexpr unsigned char Height = 42;
constexpr unsigned char Width = 42;
constexpr unsigned char Screen = 2;

constexpr unsigned char Frame_Duration = 16667;

class Game
{
public:
	Game();
	void Run();
	~Game();
private:
	sf::RenderWindow Window;
	sf::Image Icon;
	void Render();
	void Update();
	void Process();
	std::vector<std::vector<unsigned char>> matrix;
	sf::Texture Pacman_Texture , Score1_Texture;
	sf::Sprite Pacman_Sprite , Score1_Sprite;
	Pacman pacman;
};