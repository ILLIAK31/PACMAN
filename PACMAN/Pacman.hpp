#pragma once
#include <vector>

class Pacman
{
public:
	Pacman()=default;
	Pacman(std::vector<std::vector<unsigned char>>& matrix);
	~Pacman();
	int& Get_X();
	int& Get_Y();
private:
	int x, y;
};