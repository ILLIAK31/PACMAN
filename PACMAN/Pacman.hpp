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
private:
	int x, y;
};