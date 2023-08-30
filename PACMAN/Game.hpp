#pragma once
#include <array>
#include <chrono>
#include "Pacman.hpp"
#include "Menu.hpp"
#include "Matrix.hpp"

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
	sf::Texture Pacman_Texture , Score1_Texture , Score2_Texture , fruit1_Texture , PM1_Texture , PM2_Texture , PM3_Texture , Wall1_Texture , Wall2_Texture , Wall3_Texture , Wall4_Texture , Wall5_Texture , Wall6_Texture , Wall7_Texture , Wall8_Texture , Wall9_Texture , Wall10_Texture , Wall11_Texture , Wall12_Texture , Wall13_Texture , Wall14_Texture , Wall15_Texture , Wall16_Texture , Wall17_Texture , Wall18_Texture , Wall19_Texture;
	sf::Sprite Pacman_Sprite , Score1_Sprite , Score2_Sprite , fruit1_Sprite , PM1_Sprite , PM2_Sprite , PM3_Sprite , Wall1_Sprite , Wall2_Sprite , Wall3_Sprite , Wall4_Sprite , Wall5_Sprite , Wall6_Sprite , Wall7_Sprite , Wall8_Sprite , Wall9_Sprite , Wall10_Sprite , Wall11_Sprite , Wall12_Sprite , Wall13_Sprite , Wall14_Sprite , Wall15_Sprite , Wall16_Sprite , Wall17_Sprite , Wall18_Sprite , Wall19_Sprite;
	Pacman pacman;
	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::milliseconds duration, duration0{ 0 };
	int speed{1};
	float fruit1_Scale = 0.04f , cherry_Scale = 0.035f;
	Matrix matrix_setup;
};