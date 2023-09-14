#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "Pacman.hpp"
#include <string>
//
// threads
// chrono
#include <iostream>

int Game::count_of_points = 125;

Game::Game():Window(sf::VideoMode(CELL*Width*Screen, CELL*Height*Screen*1.2), "Pacman"),matrix(Width, std::vector<std::string>(Height)),pacman(matrix)
{
	Icon.loadFromFile("Icon.png");
	Window.setSize(sf::Vector2u(CELL * Width * Screen, CELL * Height * Screen * 1.1));
	Window.setIcon(48, 48, Icon.getPixelsPtr());
	Window.setFramerateLimit(10);

	Setup_Textures();

	matrix_setup.Setup_Matrix(matrix);

	start = std::chrono::high_resolution_clock::now();

	matrix[pacman.Get_Y()][pacman.Get_X()] = '@';
}

void Game::Run(Menu menu)
{
	while (Window.isOpen())
	{
		//Menu
		while (!menu.Get_Menu_End() && Menu_status == true)
		{
			elapsedSeconds_0 = Clock.getElapsedTime().asSeconds();
			menu.Update(Window);
		}
		Menu_status = false;
		//Main
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		if (duration.count() >= speed + duration0.count())
		{
			duration0 = duration;
			Process();
			Update();
			Process();
			//Ghost mode
			ghost_mode_end = Clock.getElapsedTime().asSeconds();
			ghost_mode_end -= 5.2;
			if (pacman.Get_ghost_hunter_mode() == true && ghost_mode_end - ghost_mode_start >= 3)
			{
				pacman.Get_ghost_hunter_mode() = false;
			}
		}
		//Ending
		if (count_of_points == 0 || pacman.Get_Lifes() == 0)
		{
			matrix[pacman.Get_Y()][pacman.Get_X()] = "";
			//Ghosts code here
			if (Score > Best_score)
				Best_score = Score;

			//Game over text
			float Game_Scale = 0.1f;
			if (!Game_Texture.loadFromFile("Game.png")) {}
			Game_Sprite.setTexture(Game_Texture);
			Game_Sprite.setScale(Game_Scale, Game_Scale);
			if (!Over_Texture.loadFromFile("Over.png")) {}
			Over_Sprite.setTexture(Over_Texture);
			Over_Sprite.setScale(Game_Scale, Game_Scale);
			matrix[28][15] = "Game";
			matrix[28][21] = "Over";

			//Music
			sf::Music Music2;
			if (!Music2.openFromFile("sound2.wav")){}
			else
			{
				auto start_time = std::chrono::steady_clock::now();
				auto duration = std::chrono::seconds(5);
				auto end_time = start_time + duration;
				Music2.play();
				Render();
				while (std::chrono::high_resolution_clock::now() < end_time){}
				Music2.stop();
			}
			Window.close();
		}
	}
}

void Game::Render()
{
	Window.clear();
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * Width, CELL * Height*1.1)));
	sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));
	sf::CircleShape cell2(1.5) , cell3(4);

	fruit1_Sprite.setPosition(35 * CELL, 38 * CELL * 1.11);
	fruit1_Sprite.setScale(fruit1_Scale, fruit1_Scale);
	Window.draw(fruit1_Sprite);

	if (pacman.Get_Lifes() == 1)
	{
		PM1_Sprite.setPosition(CELL, 38 * CELL * 1.11);
		Window.draw(PM1_Sprite);
	}
	else if (pacman.Get_Lifes() == 2)
	{
		PM1_Sprite.setPosition(CELL, 38 * CELL * 1.11);
		Window.draw(PM1_Sprite);
		PM2_Sprite.setPosition(4 * CELL, 38 * CELL * 1.11);
		Window.draw(PM2_Sprite);
	}
	else if (pacman.Get_Lifes() == 3)
	{
		PM1_Sprite.setPosition(CELL, 38 * CELL * 1.11);
		Window.draw(PM1_Sprite);
		PM2_Sprite.setPosition(4 * CELL, 38 * CELL * 1.11);
		Window.draw(PM2_Sprite);
		PM3_Sprite.setPosition(7 * CELL, 38 * CELL * 1.11);
		Window.draw(PM3_Sprite);
	}

	Score1_Sprite.setPosition(10, 4);
	Window.draw(Score1_Sprite);
	Score2_Sprite.setPosition(25 * CELL, 4);
	Window.draw(Score2_Sprite);

	for (int height = 0; height < Height; ++height)
	{
		for (int width = 0; width < Width; ++width)
		{
			Print(height, width, cell, cell2, cell3);
		}
	}
	Window.display();
}

void Game::Update()
{	
	Render();
	//beggin sound and pause
	elapsedSeconds = Clock.getElapsedTime().asSeconds();
	elapsedSeconds -= elapsedSeconds_0;
	if (Clock_status == true)
	{
		sf::Music Music;
		if (!Music.openFromFile("sound1.wav")){}
		else
		{
			Music.play();
			while (elapsedSeconds < 4.6 && Clock_status == true)
			{
				elapsedSeconds = Clock.getElapsedTime().asSeconds();
				elapsedSeconds -= elapsedSeconds_0;
			}
			Music.stop();
		}
	}
	Clock_status = false;
	// Cherry logic
	elapsedSeconds2 = Clock.getElapsedTime().asSeconds();
	elapsedSeconds2 -= elapsedSeconds_0 + 4.5;
	if (elapsedSeconds2 >= elapsedSeconds2_0 + 15 && matrix[38][20] == "cherry" && Cherry_status)
	{
		elapsedSeconds2_0 = elapsedSeconds2;
		matrix[38][20] = "";
	}
	else if (elapsedSeconds2 >= elapsedSeconds2_0 + 15 && matrix[38][20] == " " && Cherry_status)
	{
		elapsedSeconds2_0 = elapsedSeconds2;
		matrix[38][20] = "cherry";
	}
	//Pacman move
	if (pacman.Direction == 'R'&&pacman.Check_collision_right(matrix))
	{
		matrix[pacman.Get_Y()][pacman.Get_X()] = " ";
		pacman.Get_X() += 1;
		if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*")
		{
			--count_of_points;
			Score += 10;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*P")
		{
			pacman.Get_ghost_hunter_mode() = true;
			ghost_mode_start = Clock.getElapsedTime().asSeconds();
			Score += 50;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "cherry")
		{
			Cherry_status = false;
			matrix[pacman.Get_Y()][pacman.Get_X()] = "";
			Score += 100;
		}
		if (pacman.Get_Y() == 22 && pacman.Get_X() + 2 >= 41)
			pacman.Get_X() = 0;
		matrix[pacman.Get_Y()][pacman.Get_X()] = '@';
	}
	else if (pacman.Direction == 'L' && pacman.Check_collision_left(matrix))
	{
		matrix[pacman.Get_Y()][pacman.Get_X()] = " ";
		pacman.Get_X() -= 1;
		if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*")
		{
			--count_of_points;
			Score += 10;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*P")
		{
			pacman.Get_ghost_hunter_mode() = true;
			ghost_mode_start = Clock.getElapsedTime().asSeconds();
			Score += 50;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "cherry")
		{
			Cherry_status = false;
			matrix[pacman.Get_Y()][pacman.Get_X()] = "";
			Score += 100;
		}
		if (pacman.Get_Y() == 22 && pacman.Get_X() - 2 <= 0)
			pacman.Get_X() = 41;
		matrix[pacman.Get_Y()][pacman.Get_X()] = '@';
	}
	else if (pacman.Direction == 'U' && pacman.Check_collision_up(matrix))
	{
		matrix[pacman.Get_Y()][pacman.Get_X()] = " ";
		pacman.Get_Y() -= 1;
		if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*")
		{
			--count_of_points;
			Score += 10;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*P")
		{
			pacman.Get_ghost_hunter_mode() = true;
			ghost_mode_start = Clock.getElapsedTime().asSeconds();
			Score += 50;
		}
		matrix[pacman.Get_Y()][pacman.Get_X()] = '@';
	}
	else if (pacman.Direction == 'D' && pacman.Check_collision_down(matrix))
	{
		matrix[pacman.Get_Y()][pacman.Get_X()] = " ";
		pacman.Get_Y() += 1;
		if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*")
		{
			--count_of_points;
			Score += 10;
		}
		else if (matrix[pacman.Get_Y()][pacman.Get_X()] == "*P")
		{
			pacman.Get_ghost_hunter_mode() = true;
			ghost_mode_start = Clock.getElapsedTime().asSeconds();
			Score += 50;
		}
		matrix[pacman.Get_Y()][pacman.Get_X()] = '@';
	}

}

void Game::Process()
{
	sf::Event Event;
	while (Window.pollEvent(Event))
		if (Event.type == sf::Event::Closed)
			Window.close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pacman.Check_collision_right(matrix))
	{
		pacman.Direction = 'R';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pacman.Check_collision_left(matrix))
	{
		pacman.Direction = 'L';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pacman.Check_collision_up(matrix))
	{
		pacman.Direction = 'U';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pacman.Check_collision_down(matrix))
	{
		pacman.Direction = 'D';
	}
}

void Game::Setup_Textures()
{
	float Score1_Scale = 0.075f, Score2_Scale = 0.19f, PM_Scale = 0.065f, Wall_Scale = 0.055f;
	float  Pacman0_Scale = 0.075f , Pacman1_Scale = 0.075f;

	if (!Pacman0_Texture.loadFromFile("pacman_body0.png")) {}
	Pacman0_Sprite.setTexture(Pacman0_Texture);
	Pacman0_Sprite.setScale(Pacman0_Scale, Pacman0_Scale);

	if (!Pacman1_Texture.loadFromFile("pacman_body1.png")) {}
	Pacman1_Sprite.setTexture(Pacman1_Texture);
	Pacman1_Sprite.setScale(Pacman1_Scale, Pacman1_Scale);

	if (!Pacman2_Texture.loadFromFile("pacman_body2.png")) {}
	Pacman2_Sprite.setTexture(Pacman2_Texture);
	Pacman2_Sprite.setScale(Pacman1_Scale, Pacman1_Scale);

	if (!Pacman3_Texture.loadFromFile("pacman_body3.png")) {}
	Pacman3_Sprite.setTexture(Pacman3_Texture);
	Pacman3_Sprite.setScale(Pacman1_Scale, Pacman1_Scale);

	if (!Pacman4_Texture.loadFromFile("pacman_body4.png")) {}
	Pacman4_Sprite.setTexture(Pacman4_Texture);
	Pacman4_Sprite.setScale(Pacman1_Scale, Pacman1_Scale);

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

	if (!Wall8_Texture.loadFromFile("8.png")) {}
	Wall8_Sprite.setTexture(Wall8_Texture);
	Wall8_Sprite.setScale(0.050f, 0.055f);

	if (!Wall9_Texture.loadFromFile("9.png")) {}
	Wall9_Sprite.setTexture(Wall9_Texture);
	Wall9_Sprite.setScale(0.025f, 0.035f);

	if (!Wall10_Texture.loadFromFile("10.png")) {}
	Wall10_Sprite.setTexture(Wall10_Texture);
	Wall10_Sprite.setScale(0.035f, 0.020f);

	if (!Wall11_Texture.loadFromFile("11.png")) {}
	Wall11_Sprite.setTexture(Wall11_Texture);
	Wall11_Sprite.setScale(0.030f, 0.025f);

	if (!Wall12_Texture.loadFromFile("12.png")) {}
	Wall12_Sprite.setTexture(Wall12_Texture);
	Wall12_Sprite.setScale(0.030f, 0.025f);

	if (!Wall13_Texture.loadFromFile("13.png")) {}
	Wall13_Sprite.setTexture(Wall13_Texture);
	Wall13_Sprite.setScale(0.050f, 0.055f);

	if (!Wall14_Texture.loadFromFile("14.png")) {}
	Wall14_Sprite.setTexture(Wall14_Texture);
	Wall14_Sprite.setScale(0.028f, 0.032f);

	if (!Wall15_Texture.loadFromFile("15.png")) {}
	Wall15_Sprite.setTexture(Wall15_Texture);
	Wall15_Sprite.setScale(0.030f, 0.032f);

	if (!Wall16_Texture.loadFromFile("16.png")) {}
	Wall16_Sprite.setTexture(Wall16_Texture);
	Wall16_Sprite.setScale(0.040f, 0.035f);

	if (!Wall17_Texture.loadFromFile("17.png")) {}
	Wall17_Sprite.setTexture(Wall17_Texture);
	Wall17_Sprite.setScale(0.033f, 0.035f);

	if (!Wall18_Texture.loadFromFile("18.png")) {}
	Wall18_Sprite.setTexture(Wall18_Texture);
	Wall18_Sprite.setScale(0.055f, 0.050f);

	if (!Wall19_Texture.loadFromFile("19.png")) {}
	Wall19_Sprite.setTexture(Wall19_Texture);
	Wall19_Sprite.setScale(0.040f, 0.040f);

	if (!Wall20_Texture.loadFromFile("20.png")) {}
	Wall20_Sprite.setTexture(Wall20_Texture);
	Wall20_Sprite.setScale(0.055f, 0.075f);

	if (!Wall21_Texture.loadFromFile("21.png")) {}
	Wall21_Sprite.setTexture(Wall21_Texture);
	Wall21_Sprite.setScale(0.040f, 0.04f);

	if (!Wall22_Texture.loadFromFile("22.png")) {}
	Wall22_Sprite.setTexture(Wall22_Texture);
	Wall22_Sprite.setScale(0.04f, 0.04f);

	if (!Wall23_Texture.loadFromFile("23.png")) {}
	Wall23_Sprite.setTexture(Wall23_Texture);
	Wall23_Sprite.setScale(0.033f, 0.055f);

	if (!Wall24_Texture.loadFromFile("24.png")) {}
	Wall24_Sprite.setTexture(Wall24_Texture);
	Wall24_Sprite.setScale(0.033f, 0.030f);

	if (!Wall25_Texture.loadFromFile("25.png")) {}
	Wall25_Sprite.setTexture(Wall25_Texture);
	Wall25_Sprite.setScale(0.030f, 0.032f);

	if (!Wall26_Texture.loadFromFile("26.png")) {}
	Wall26_Sprite.setTexture(Wall26_Texture);
	Wall26_Sprite.setScale(0.055f, 0.055f);

	if (!Wall27_Texture.loadFromFile("27.png")) {}
	Wall27_Sprite.setTexture(Wall27_Texture);
	Wall27_Sprite.setScale(0.055f, 0.055f);

	if (!Wall28_Texture.loadFromFile("28.png")) {}
	Wall28_Sprite.setTexture(Wall28_Texture);
	Wall28_Sprite.setScale(0.04f, 0.04f);

	if (!Wall29_Texture.loadFromFile("29.png")) {}
	Wall29_Sprite.setTexture(Wall29_Texture);
	Wall29_Sprite.setScale(0.055f, 0.055f);

	if (!Wall30_Texture.loadFromFile("30.png")) {}
	Wall30_Sprite.setTexture(Wall30_Texture);
	Wall30_Sprite.setScale(0.055f, 0.055f);

}

void Game::Print(int height, int width, sf::RectangleShape& cell, sf::CircleShape& cell2 , sf::CircleShape& cell3)
{
	//shit I made mistake in creating of textures on the begining thats why I must pay for that with this if's fuck
	float pacman_x, pacman_y;
	if (matrix[height][width] == "#")
	{
		cell.setFillColor(sf::Color::Blue);
		cell.setPosition(CELL * width, CELL * height);
		Window.draw(cell);
	}
	else if (matrix[height][width] == "#1")
	{
		Wall1_Sprite.setPosition(width * CELL, height * CELL);
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
		Wall8_Sprite.setPosition(width * CELL * 0.97, height * CELL * 0.96);
		Window.draw(Wall8_Sprite);
	}
	else if (matrix[height][width] == "#9")
	{
		Wall9_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall9_Sprite);
	}
	else if (matrix[height][width] == "#10")
	{
		Wall10_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall10_Sprite);
	}
	else if (matrix[height][width] == "#11")
	{
		Wall11_Sprite.setPosition(width * CELL * 0.982, height * CELL);
		Window.draw(Wall11_Sprite);
	}
	else if (matrix[height][width] == "#12")
	{
		Wall12_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall12_Sprite);
	}
	else if (matrix[height][width] == "#13")
	{
		Wall13_Sprite.setPosition(width * CELL * 0.97, height * CELL * 0.96);
		Window.draw(Wall13_Sprite);
	}
	else if (matrix[height][width] == "#14")
	{
		Wall14_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall14_Sprite);
	}
	else if (matrix[height][width] == "#15")
	{
		Wall15_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall15_Sprite);
	}
	else if (matrix[height][width] == "#16")
	{
		Wall16_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall16_Sprite);
	}
	else if (matrix[height][width] == "#17")
	{
		Wall17_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall17_Sprite);
	}
	else if (matrix[height][width] == "#18")
	{
		Wall18_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall18_Sprite);
	}
	else if (matrix[height][width] == "#19")
	{
		Wall19_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall19_Sprite);
	}
	else if (matrix[height][width] == "#20")
	{
		Wall20_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall20_Sprite);
	}
	else if (matrix[height][width] == "#21")
	{
		Wall21_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall21_Sprite);
	}
	else if (matrix[height][width] == "#22")
	{
		Wall22_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall22_Sprite);
	}
	else if (matrix[height][width] == "#23")
	{
		Wall23_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall23_Sprite);
	}
	else if (matrix[height][width] == "#24")
	{
		Wall24_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall24_Sprite);
	}
	else if (matrix[height][width] == "#25")
	{
		Wall25_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall25_Sprite);
	}
	else if (matrix[height][width] == "#26")
	{
		Wall26_Sprite.setPosition(width * CELL * 0.965, height * CELL * 0.99);
		Window.draw(Wall26_Sprite);
	}
	else if (matrix[height][width] == "#27")
	{
		Wall27_Sprite.setPosition(width * CELL * 0.965, height * CELL * 0.99);
		Window.draw(Wall27_Sprite);
	}
	else if (matrix[height][width] == "#28")
	{
		Wall28_Sprite.setPosition(width * CELL, height * CELL);
		Window.draw(Wall28_Sprite);
	}
	else if (matrix[height][width] == "#29")
	{
		Wall29_Sprite.setPosition(width * CELL * 0.965, height * CELL * 0.98);
		Window.draw(Wall29_Sprite);
	}
	else if (matrix[height][width] == "#30")
	{
		Wall30_Sprite.setPosition(width * CELL * 0.965, height * CELL * 0.98);
		Window.draw(Wall30_Sprite);
	}
	else if (matrix[height][width] == "@" && pacman.Direction == 'C')
	{
		Pacman0_Sprite.setPosition(pacman.Get_X() * CELL*0.989, pacman.Get_Y() * CELL * 0.975);
		Window.draw(Pacman0_Sprite);
	}
	else if (matrix[height][width] == "@" && pacman.Direction == 'R')
	{
		pacman_x = 0.981;
		pacman_y = 0.975;
		if (pacman.Get_X() <= 20 && pacman.Get_Y() <= 10)
		{
			pacman_x = 0.95;
			pacman_y = 0.9;
		}
		else if (pacman.Get_X() >= 2 && pacman.Get_X() <= 9 && (pacman.Get_Y() == 26 || pacman.Get_Y() == 34))
		{
			pacman_x = 0.91;
		}
		else if (pacman.Get_Y() == 30 && pacman.Get_X() >= 2 && pacman.Get_X() <= 5)
		{
			pacman_x = 0.85;
		}
		else if (pacman.Get_Y() == 20)
		{
			pacman_y = 0.96;
		}
		else if (pacman.Get_Y() == 34 && pacman.Get_X() >= 13 && pacman.Get_X() <= 18)
		{
			pacman_x = 0.96;
		}
		else if (pacman.Get_Y() == 38)
		{
			pacman_y = 0.98;
		}
		else if (pacman.Get_Y() > 15 && pacman.Get_Y() <= 20 && pacman.Get_X() <= 20)
		{
			pacman_x = 0.96;
		}
		else if (pacman.Get_Y() == 22 && pacman.Get_X() > 20)
		{
			pacman_x = 1.03;
			pacman_y = 0.965;
		}
		else if (pacman.Get_Y() == 22 && pacman.Get_X() < 20)
		{
			pacman_x = 0.91;
			pacman_y = 0.965;
		}
		else if (pacman.Get_Y() == 18 && pacman.Get_X()<=20)
		{
			pacman_x = 0.9;
			pacman_y = 0.95;
		}
		else if (pacman.Get_Y() == 18 && pacman.Get_X() > 20)
		{
			pacman_x = 0.985;
			pacman_y = 0.95;
		}
		else if (pacman.Get_Y() > 10 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.98;
			pacman_y = 0.94;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_Y() > 10 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.5;
			pacman_y = 0.9;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_Y() <= 10)
		{
			pacman_y = 0.9;
		}
		Pacman1_Sprite.setPosition(pacman.Get_X()*CELL*pacman_x, pacman.Get_Y()*CELL * pacman_y);
		Window.draw(Pacman1_Sprite);
	}
	else if (matrix[height][width] == "@" && pacman.Direction == 'L')
	{
		pacman_x = 0.915;
		pacman_y = 0.975;
		if (pacman.Get_X() <= 20 && pacman.Get_Y() <= 10)
		{
			pacman_x = 0.87;
			pacman_y = 0.9;
		}
		else if (pacman.Get_Y() == 30 && pacman.Get_X() >= 36 && pacman.Get_X() <= 39)
		{
			pacman_x = 0.99;
		}
		else if (pacman.Get_X() >= 32 && pacman.Get_X() <= 39 && (pacman.Get_Y() == 26 || pacman.Get_Y() == 34))
		{
			pacman_x = 0.98;
		}
		else if (pacman.Get_Y() == 34 && pacman.Get_X() >= 13 && pacman.Get_X() <= 18)
		{
			pacman_x = 0.96;
		}
		else if (pacman.Get_Y() == 34 && pacman.Get_X() >= 23 && pacman.Get_X() <= 28)
		{
			pacman_x = 0.98;
		}
		else if (pacman.Get_Y() > 15 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.96;
			pacman_y = 0.96;
		}
		else if (pacman.Get_Y() == 22 && pacman.Get_X() > 20)
		{
			pacman_x = 0.985;
			pacman_y = 0.965;
		}
		else if (pacman.Get_Y() == 22 && pacman.Get_X() <= 20)
		{
			pacman_x = 0.75;
			pacman_y = 0.965;
		}
		else if (pacman.Get_Y() == 18 && pacman.Get_X() > 20)
		{
			pacman_x = 0.985;
			pacman_y = 0.95;
		}
		else if (pacman.Get_Y() == 38)
		{
			pacman_y = 0.98;
		}
		else if (pacman.Get_X() <= 20 && pacman.Get_Y() > 10 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.9;
			pacman_y = 0.95;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_Y() > 10 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.95;
			pacman_y = 0.94;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_Y() <= 10)
		{
			pacman_x = 0.97;
			pacman_y = 0.9;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_Y() >= 20)
		{
			pacman_x = 0.95;
			pacman_y = 0.975;
		}
		Pacman2_Sprite.setPosition(pacman.Get_X() * CELL*pacman_x, pacman.Get_Y() * CELL * pacman_y);
		Window.draw(Pacman2_Sprite);
	}
	else if (matrix[height][width] == "@" && pacman.Direction == 'U')
	{
		pacman_x = 1;
		pacman_y = 0.92;
		if (pacman.Get_X() == 13)
		{
			pacman_x = 0.947;
			pacman_y = 0.955;
		}
		else if (pacman.Get_X() == 5&& pacman.Get_Y() >= 30)
		{
			pacman_x = 0.85;
			pacman_y = 0.98;
		}
		else if (pacman.Get_X() == 36 && pacman.Get_Y() >= 30)
		{
			pacman_x = 0.98;
			pacman_y = 0.98;
		}
		else if (pacman.Get_X() == 2 && pacman.Get_Y() > 20)
		{
			pacman_x = 0.7;
			pacman_y = 0.975;
		}
		else if ((pacman.Get_X() == 18 || pacman.Get_X() == 23) && pacman.Get_Y() >= 34 && pacman.Get_Y() <= 38)
		{
			pacman_x = 0.965;
			pacman_y = 0.98;
		}
		else if (pacman.Get_X() == 39 && pacman.Get_Y() > 20)
		{
			pacman_x = 0.98;
			pacman_y = 0.98;
		}
		else if (pacman.Get_X() == 23 && pacman.Get_Y() == 18)
		{
			pacman_x = 0.97;
			pacman_y = 0.975;
		}
		else if (pacman.Get_X() == 18 && pacman.Get_Y() == 18)
		{
			pacman_x = 0.96;
			pacman_y = 0.975;
		}
		else if (pacman.Get_X() == 2 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.7;
			pacman_y = 0.9;
		}
		else if (pacman.Get_X() == 28)
		{
			pacman_x = 0.978;
			pacman_y = 0.955;
		}
		else if (pacman.Get_X() == 18)
		{
			pacman_x = 0.96;
			pacman_y = 0.94;
		}
		else if (pacman.Get_X() == 23)
		{
			pacman_x = 0.965;
			pacman_y = 0.92;
		}
		else if (pacman.Get_X() > 13 && pacman.Get_X() < 20 && pacman.Get_Y() > 16)
		{
			pacman_y = 0.97;
		}
		else if (pacman.Get_X() > 20 && pacman.Get_X() < 28 && pacman.Get_Y() > 16)
		{
			pacman_y = 0.975;
		}
		else if (pacman.Get_X() <= 20)
			pacman_x = 0.915;
		else if (pacman.Get_X() > 20)
			pacman_x = 0.978;
		Pacman3_Sprite.setPosition(pacman.Get_X() * CELL*pacman_x, pacman.Get_Y() * CELL * pacman_y);
		Window.draw(Pacman3_Sprite);
	}
	else if (matrix[height][width] == "@" && pacman.Direction == 'D')
	{
		pacman_x = 0.98;
		pacman_y = 0.98;
		if (pacman.Get_X() == 2 && pacman.Get_Y() <= 20)
		{
			pacman_x = 0.7;
			pacman_y = 0.96;
		}
		else if (pacman.Get_X() == 5 && pacman.Get_Y() >= 30)
		{
			pacman_x = 0.85;
			pacman_y = 0.98;
		}
		else if ((pacman.Get_X() == 18 || pacman.Get_X() == 23)  && pacman.Get_Y() >= 34 && pacman.Get_Y() <= 38)
		{
			pacman_x = 0.965;
			pacman_y = 0.985;
		}
		else if (pacman.Get_X() == 2 && pacman.Get_Y() > 20)
		{
			pacman_x = 0.7;
			pacman_y = 0.975;
		}
		else if (pacman.Get_X() == 23 && pacman.Get_Y() >= 18 && pacman.Get_Y() <= 20)
		{
			pacman_y = 0.97;
		}
		else if (pacman.Get_X() == 9)
		{
			pacman_x = 0.91;
		}
		else if (pacman.Get_X() == 18)
		{
			pacman_x = 0.96;
			pacman_y = 0.95;
		}
		else if (pacman.Get_X() == 23)
		{
			pacman_x = 0.965;
			pacman_y = 0.92;
		}
		else if (pacman.Get_X() == 13)
		{
			pacman_x = 0.947;
		}
		else if (pacman.Get_X() == 28)
		{
			pacman_x = 0.975;
		}
		Pacman4_Sprite.setPosition(pacman.Get_X() * CELL * pacman_x, pacman.Get_Y() * CELL * pacman_y);
		Window.draw(Pacman4_Sprite);
		}
	else if (matrix[height][width] == "*")
	{

		cell2.setFillColor(sf::Color::White);
		cell2.setPosition(CELL * width * 1.013, CELL * height * 1.02);
		Window.draw(cell2);
	}
	else if (matrix[height][width] == "cherry")
	{
		fruit1_Sprite.setPosition(width * CELL, height * CELL * 0.985);
		fruit1_Sprite.setScale(cherry_Scale, cherry_Scale);
		Window.draw(fruit1_Sprite);
	}
	else if (matrix[height][width] == "*P")
	{
		cell3.setFillColor(sf::Color::White);
		cell3.setPosition(CELL * width, CELL * height);
		Window.draw(cell3);
	}
	else if (matrix[height][width] == "Game")
	{
		Game_Sprite.setPosition(width * CELL, height * CELL*0.98);
		Window.draw(Game_Sprite);
	}
	else if (matrix[height][width] == "Over")
	{
		Over_Sprite.setPosition(width * CELL, height * CELL*0.98);
		Window.draw(Over_Sprite);
	}
	else if (matrix[height][width] == "N2_1")
	{
		path = "N";
		path += (std::to_string(Score))[0];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL, height * CELL*1.27);
		Window.draw(N2_Sprite);
	}
	else if (matrix[height][width] == "N2_2" && (std::to_string(Score)).size() > 1)
	{
		path = "N";
		path += (std::to_string(Score))[1];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL*0.98, height * CELL * 1.27);
		Window.draw(N2_Sprite);
	}
	else if (matrix[height][width] == "N2_3" && (std::to_string(Score)).size() > 2)
	{
		path = "N";
		path += (std::to_string(Score))[2];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL * 0.97, height * CELL * 1.27);
		Window.draw(N2_Sprite);
	}
	else if (matrix[height][width] == "N2_4" && (std::to_string(Score)).size() > 3)
	{
		path = "N";
		path += (std::to_string(Score))[3];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL * 0.96, height * CELL * 1.27);
		Window.draw(N2_Sprite);
	}
	else if (matrix[height][width] == "N2_5" && (std::to_string(Score)).size() > 4)
	{
		path = "N";
		path += (std::to_string(Score))[4];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL * 0.98, height * CELL * 1.27);
		Window.draw(N2_Sprite);
	}
	else if (matrix[height][width] == "N2_6" && (std::to_string(Score)).size() > 5)
	{
		path = "N";
		path += (std::to_string(Score))[5];
		path += ".png";
		if (!N2_Texture.loadFromFile(path)) {}
		N2_Sprite.setTexture(N2_Texture);
		N2_Sprite.setScale(0.03f, 0.03f);
		N2_Sprite.setPosition(width * CELL * 0.98, height * CELL * 1.27);
		Window.draw(N2_Sprite);
	}
}

Game::~Game(){}