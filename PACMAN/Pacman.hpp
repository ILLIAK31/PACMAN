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
	bool Check_collision_with_ghost(std::vector<std::vector<std::string>>& matrix);
	friend bool operator==(std::string str,std::vector<std::string> obj);
	std::vector<std::string>& Get_ghost_names();
private:
	int x, y, lifes{3};
	bool ghost_hunter_mode{ false };
	int Animation_status{1};
	std::vector<std::string> ghost_names;
};