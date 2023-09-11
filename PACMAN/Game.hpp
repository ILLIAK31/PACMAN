#pragma once
#include <chrono>
#include "Pacman.hpp"
#include "Menu.hpp"
#include "Matrix.hpp"


constexpr unsigned char CELL = 8;
constexpr unsigned char Height = 42;
constexpr unsigned char Width = 42;
constexpr unsigned char Screen = 2;

class Game
{
	friend class Menu;
public:
	Game();
	void Run(Menu menu);
	~Game();
private:
	static int count_of_points;
	sf::RenderWindow Window;
	sf::Image Icon;
	void Render();
	void Update();
	void Process();
	void Setup_Textures();
	void Print(int height , int width , sf::RectangleShape& cell , sf::CircleShape& cell2 , sf::CircleShape& cell3);
	std::vector<std::vector<std::string>> matrix;
	sf::Texture Pacman0_Texture , Pacman1_Texture , Pacman2_Texture, Pacman3_Texture , Pacman4_Texture, Score1_Texture , Score2_Texture , fruit1_Texture , PM1_Texture , PM2_Texture , PM3_Texture , Wall1_Texture , Wall2_Texture , Wall3_Texture , Wall4_Texture , Wall5_Texture , Wall6_Texture , Wall7_Texture , Wall8_Texture , Wall9_Texture , Wall10_Texture , Wall11_Texture , Wall12_Texture , Wall13_Texture , Wall14_Texture , Wall15_Texture , Wall16_Texture , Wall17_Texture , Wall18_Texture , Wall19_Texture , Wall20_Texture, Wall21_Texture , Wall22_Texture , Wall23_Texture , Wall24_Texture , Wall25_Texture , Wall26_Texture , Wall27_Texture , Wall28_Texture , Wall29_Texture , Wall30_Texture;
	sf::Sprite Pacman0_Sprite, Pacman1_Sprite , Pacman2_Sprite, Pacman3_Sprite, Pacman4_Sprite, Score1_Sprite , Score2_Sprite , fruit1_Sprite , PM1_Sprite , PM2_Sprite , PM3_Sprite , Wall1_Sprite , Wall2_Sprite , Wall3_Sprite , Wall4_Sprite , Wall5_Sprite , Wall6_Sprite , Wall7_Sprite , Wall8_Sprite , Wall9_Sprite , Wall10_Sprite , Wall11_Sprite , Wall12_Sprite , Wall13_Sprite , Wall14_Sprite , Wall15_Sprite , Wall16_Sprite , Wall17_Sprite , Wall18_Sprite , Wall19_Sprite , Wall20_Sprite , Wall21_Sprite , Wall22_Sprite , Wall23_Sprite , Wall24_Sprite , Wall25_Sprite , Wall26_Sprite , Wall27_Sprite , Wall28_Sprite , Wall29_Sprite , Wall30_Sprite;
	Pacman pacman;
	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::milliseconds duration, duration0{ 0 };
	int speed{ 130 }, Score{0};
	float fruit1_Scale = 0.04f, cherry_Scale = 0.035f, elapsedSeconds, elapsedSeconds_0, elapsedSeconds2, elapsedSeconds2_0{0};
	Matrix matrix_setup;
	sf::Clock Clock;
	bool Clock_status{ true }, Menu_status{ true }, Cherry_status{true};
};