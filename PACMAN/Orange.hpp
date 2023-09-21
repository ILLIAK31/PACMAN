#pragma once

#include "Ghost.hpp"

class Orange : public Ghost
{
public:
	Orange() = default;
	Orange(int X, int Y);
	~Orange();
private:
};