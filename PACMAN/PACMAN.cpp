#include "Pacman.hpp"

Pacman::Pacman(std::vector<std::vector<unsigned char>>& matrix):x(0),y(0)
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

Pacman::~Pacman(){}