#include "Ghost.hpp"

char& Ghost::Get_Direction()
{
	return this->Direction;
}

int& Ghost::Get_X()
{
	return this->x;
}

int& Ghost::Get_Y()
{
	return this->y;
}

Ghost::~Ghost(){}