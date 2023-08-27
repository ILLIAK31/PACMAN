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
private:
	int x, y, lifes{3};
};