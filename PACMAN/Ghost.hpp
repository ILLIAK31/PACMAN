#pragma once

class Ghost
{
public:
	Ghost()=default;
	~Ghost();
	char& Get_Direction();
	int& Get_X();
	int& Get_Y();
private:
	char Direction;
	int x{0}, y{0};
};
