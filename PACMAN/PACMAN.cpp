#include "Pacman.hpp"

Pacman::Pacman(std::vector<std::vector<std::string>>& matrix):x(20),y(28)
{
	matrix[this->x][this->y] = '@';
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