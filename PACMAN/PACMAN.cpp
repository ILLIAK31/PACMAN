#include "Pacman.hpp"

Pacman::Pacman(std::vector<std::vector<std::string>>& matrix):x(20),y(28){}

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

bool Pacman::Check_collision_right(std::vector<std::vector<std::string>>& matrix)
{
	if (((matrix[this->y][this->x + 2] == " ")||(matrix[this->y][this->x+2] == "*")) && (matrix[this->y -1][this->x+2] == " ") && (matrix[this->y + 1][this->x+2] == " "))
		return true;
	return false;
}

Pacman::~Pacman(){}