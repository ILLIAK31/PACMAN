#pragma once

#include "Ghost.hpp"

class Blue : public Ghost
{
public:
	Blue() = default;
	Blue(int X, int Y);
	~Blue();
private:
};