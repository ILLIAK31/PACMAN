#include "Pacman.hpp"
#include <string>

Pacman::Pacman(std::vector<std::vector<std::string>>& matrix):x(0),y(0)
{
	matrix[0][0] = '@';
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

Pacman::~Pacman(){}