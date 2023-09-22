#include "Pacman.hpp"

Pacman::Pacman(std::vector<std::vector<std::string>>& matrix):x(20),y(28)
{
	ghost_names.push_back("G1");
	ghost_names.push_back("G2");
	ghost_names.push_back("G3");
	ghost_names.push_back("G4");
}

int& Pacman::Get_X()
{
	return this->x;
}

int& Pacman::Get_Y()
{
	return this->y;
}

int& Pacman::Get_Lifes()
{
	return this->lifes;
}

bool& Pacman::Get_ghost_hunter_mode()
{
	return this->ghost_hunter_mode;
}

int& Pacman::Get_animation_status()
{
	return this->Animation_status;
}

bool Pacman::Check_collision_right(std::vector<std::vector<std::string>>& matrix)
{
	if (this->y == 22 && this->x + 2 >= 41)
		return true;
	if (((matrix[this->y][this->x + 2] == " ")||(matrix[this->y][this->x+2] == "*")|| (matrix[this->y][this->x + 2] == "*P") || (matrix[this->y][this->x + 2] == "cherry")) && ((matrix[this->y -1][this->x+2] == " ")|| (matrix[this->y - 1][this->x + 2] == "*")|| (matrix[this->y - 1][this->x + 2] == "*P") || (matrix[this->y - 1][this->x + 2] == "cherry")) && ((matrix[this->y + 1][this->x+2] == " ")|| (matrix[this->y + 1][this->x + 2] == "*")|| (matrix[this->y + 1][this->x + 2] == "*P") || (matrix[this->y + 1][this->x + 2] == "cherry")))
		return true;
	return false;
}

bool Pacman::Check_collision_left(std::vector<std::vector<std::string>>& matrix)
{
	if (this->y == 22 && this->x - 2 <= 0)
		return true;
	if (((matrix[this->y][this->x - 2] == " ") || (matrix[this->y][this->x - 2] == "*")|| (matrix[this->y][this->x - 2] == "*P") || (matrix[this->y][this->x - 2] == "cherry")) && ((matrix[this->y - 1][this->x - 2] == " ")|| (matrix[this->y - 1][this->x - 2] == "*")|| (matrix[this->y - 1][this->x - 2] == "*P") || (matrix[this->y - 1][this->x - 2] == "cherry")) && ((matrix[this->y + 1][this->x - 2] == " ")|| (matrix[this->y + 1][this->x - 2] == "*") || (matrix[this->y + 1][this->x - 2] == "*P") || (matrix[this->y + 1][this->x - 2] == "cherry")))
		return true;
	return false;
}

bool Pacman::Check_collision_up(std::vector<std::vector<std::string>>& matrix)
{
	if (((matrix[this->y-2][this->x] == " ") || (matrix[this->y-2][this->x] == "*") || (matrix[this->y - 2][this->x] == "*P") || (matrix[this->y - 2][this->x] == "cherry")) && ((matrix[this->y - 2][this->x - 1] == " ")|| (matrix[this->y - 2][this->x - 1] == "*") || (matrix[this->y - 2][this->x - 1] == "*P")|| (matrix[this->y - 2][this->x - 1] == "cherry")) && ((matrix[this->y - 2][this->x + 1] == " ")|| (matrix[this->y - 2][this->x + 1] == "*")||(matrix[this->y - 2][this->x + 1] == "*P") || (matrix[this->y - 2][this->x + 1] == "cherry")))
		return true;
	return false;
}

bool Pacman::Check_collision_down(std::vector<std::vector<std::string>>& matrix)
{
	if (this->y + 2 == 22 && this->x >= 19 && this->x <= 22)
		return false;
	if (((matrix[this->y + 2][this->x] == " ") || (matrix[this->y + 2][this->x] == "*") || (matrix[this->y + 2][this->x] == "*P") || (matrix[this->y + 2][this->x] == "cherry")) && ((matrix[this->y + 2][this->x - 1] == " ") || (matrix[this->y + 2][this->x - 1] == "*") || (matrix[this->y + 2][this->x - 1] == "*P")||(matrix[this->y + 2][this->x - 1] == "cherry")) && ((matrix[this->y + 2][this->x + 1] == " ") || (matrix[this->y + 2][this->x + 1] == "*") || (matrix[this->y + 2][this->x + 1] == "*P") || (matrix[this->y + 2][this->x + 1] == "cherry")))
		return true;
	return false;
}

bool operator==(std::string str, std::vector<std::string> obj)
{
	return ((str == obj[0])||(str == obj[1])||(str == obj[2])||(str == obj[3])) ? true : false;
}

bool Pacman::Check_collision_with_ghost(std::vector<std::vector<std::string>>& matrix)
{
	return ((matrix[this->y][this->x + 1] == ghost_names)||(matrix[this->y][this->x - 1] == ghost_names)||(matrix[this->y+1][this->x] == ghost_names)||(matrix[this->y-1][this->x] == ghost_names))?true:false;
}

std::vector<std::string>& Pacman::Get_ghost_names()
{
	return this->ghost_names;
}

Pacman::~Pacman(){}