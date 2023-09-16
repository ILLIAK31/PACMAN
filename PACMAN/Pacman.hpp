#pragma once
#include <vector>
#include <string>

class Pacman
{
public:
	Pacman()=default;
	Pacman(std::vector<std::vector<std::string>>& matrix);
	~Pacman();
	int& Get_X();
	int& Get_Y();
	int& Get_Lifes();
	char Direction{'C'};
	bool& Get_ghost_hunter_mode();
	int& Get_animation_status();
	bool Check_collision_right(std::vector<std::vector<std::string>>& matrix) , Check_collision_left(std::vector<std::vector<std::string>>& matrix), Check_collision_up(std::vector<std::vector<std::string>>& matrix) , Check_collision_down(std::vector<std::vector<std::string>>& matrix);
private:
	int x, y, lifes{3};
	bool ghost_hunter_mode{ false };
	int Animation_status{1};
};