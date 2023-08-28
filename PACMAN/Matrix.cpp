#include "Matrix.hpp"
#include <vector>
#include <string>

Matrix::Matrix(){}

Matrix::~Matrix(){}

void Matrix::Setup_Matrix(std::vector<std::vector<std::string>>& matrix)
{
	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height == 5 && width >= 0 && width <= 42)
				matrix[height][width] = "#";
	}
	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height > 5 && (width == 0 || width == 41) && height <= 39)
				matrix[height][width] = "#";
	}
	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height == 40 && width >= 0 && width <= 42)
				matrix[height][width] = "#";
	}

	matrix[9][4] = matrix[9][5] = matrix[9][6] = matrix[9][7] = matrix[10][4] = matrix[11][4] = matrix[11][5] = matrix[11][6] = matrix[11][7] = matrix[10][7] = "#";
	matrix[9][37] = matrix[9][36] = matrix[9][35] = matrix[9][34] = matrix[10][37] = matrix[10][34] = matrix[11][37] = matrix[11][36] = matrix[11][35] = matrix[11][34] = "#";

	matrix[6][20] = matrix[7][20] = matrix[8][20] = matrix[9][20] = matrix[10][20] = matrix[11][20] = matrix[6][21] = matrix[7][21] = matrix[8][21] = matrix[9][21] = matrix[10][21] = matrix[11][21] = "#";

	matrix[9][12] = matrix[9][13] = matrix[9][14] = matrix[9][15] = matrix[9][16] = matrix[9][11] = matrix[10][11] = matrix[10][16] = matrix[11][12] = matrix[11][13] = matrix[11][14] = matrix[11][15] = matrix[11][16] = matrix[11][11] = "#";
	matrix[9][30] = matrix[9][29] = matrix[9][28] = matrix[9][27] = matrix[9][26] = matrix[9][25] = matrix[10][25] = matrix[10][30] = matrix[11][29] = matrix[11][28] = matrix[11][27] = matrix[11][26] = matrix[11][25] = matrix[11][30] = "#";

	matrix[15][4] = matrix[15][5] = matrix[15][6] = matrix[15][7] = matrix[16][4] = matrix[16][5] = matrix[16][6] = matrix[16][7] = "#";
	matrix[15][37] = matrix[15][36] = matrix[15][35] = matrix[15][34] = matrix[16][37] = matrix[16][36] = matrix[16][35] = matrix[16][34] = "#";

	matrix[20][1] = matrix[20][2] = matrix[20][3] = matrix[20][4] = matrix[20][5] = matrix[20][6] = matrix[20][7] = "#";
	matrix[20][41] = matrix[20][40] = matrix[20][39] = matrix[20][38] = matrix[20][37] = matrix[20][36] = matrix[20][35] = matrix[20][34] = "#";

	matrix[24][1] = matrix[24][2] = matrix[24][3] = matrix[24][4] = matrix[24][5] = matrix[24][6] = matrix[24][7] = "#";
	matrix[24][41] = matrix[24][40] = matrix[24][39] = matrix[24][38] = matrix[24][37] = matrix[24][36] = matrix[24][35] = matrix[24][34] = "#";

	matrix[21][0] = matrix[22][0] = matrix[23][0] = matrix[21][41] = matrix[22][41] = matrix[23][41] = "";

	matrix[32][1] = matrix[32][2] = matrix[32][3] = "#";
	matrix[32][40] = matrix[32][39] = matrix[32][38] = "#";

	matrix[15][20] = matrix[16][20] = matrix[17][20] = matrix[18][20] = matrix[15][21] = matrix[16][21] = matrix[17][21] = matrix[18][21] = matrix[15][19] = matrix[15][18] = matrix[15][17] = matrix[15][16] = matrix[15][15] = matrix[16][19] = matrix[16][18] = matrix[16][17] = matrix[16][16] = matrix[16][15] = matrix[15][22] = matrix[15][23] = matrix[15][24] = matrix[15][25] = matrix[15][26] = matrix[16][22] = matrix[16][23] = matrix[16][24] = matrix[16][25] = matrix[16][26] = "#";

	matrix[22][15] = matrix[22][16] = matrix[22][17] = matrix[22][18] = matrix[22][19] = matrix[22][20] = matrix[22][21] = matrix[22][22] = matrix[22][23] = matrix[22][24] = matrix[22][25] = matrix[22][26] = matrix[23][15] = matrix[24][15] = matrix[25][15] = matrix[23][26] = matrix[24][26] = matrix[25][26] = matrix[26][15] = matrix[26][16] = matrix[26][17] = matrix[26][18] = matrix[26][19] = matrix[26][20] = matrix[26][21] = matrix[26][22] = matrix[26][23] = matrix[26][24] = matrix[26][25] = matrix[26][26] = "#";

	matrix[32][15] = matrix[32][16] = matrix[32][17] = matrix[32][18] = matrix[32][19] = matrix[32][20] = matrix[32][21] = matrix[32][22] = matrix[32][23] = matrix[32][24] = matrix[32][25] = matrix[32][26] = matrix[31][15] = matrix[31][16] = matrix[31][17] = matrix[31][18] = matrix[31][19] = matrix[31][20] = matrix[31][21] = matrix[31][22] = matrix[31][23] = matrix[31][24] = matrix[31][25] = matrix[31][26] = matrix[30][15] = matrix[30][16] = matrix[30][17] = matrix[30][18] = matrix[30][19] = matrix[30][20] = matrix[30][21] = matrix[30][22] = matrix[30][23] = matrix[30][24] = matrix[30][25] = matrix[30][26] = matrix[31][20] = matrix[31][21] = matrix[32][20] = matrix[32][21] = matrix[33][20] = matrix[33][21] = matrix[34][20] = matrix[34][21] = matrix[35][20] = matrix[35][21] = matrix[36][20] = matrix[36][21] = "#";

	matrix[36][4] = matrix[36][5] = matrix[36][6] = matrix[36][7] = matrix[36][8] = matrix[36][9] = matrix[36][10] = matrix[36][11] = matrix[36][12] = matrix[36][13] = matrix[36][14] = matrix[36][15] = matrix[36][16] = matrix[35][11] = matrix[34][11] = matrix[33][11] = matrix[32][11] = matrix[31][11] = matrix[30][11] = "#";
	matrix[36][37] = matrix[36][36] = matrix[36][35] = matrix[36][34] = matrix[36][33] = matrix[36][32] = matrix[36][31] = matrix[36][30] = matrix[36][29] = matrix[36][28] = matrix[36][27] = matrix[36][26] = matrix[36][25] = matrix[35][30] = matrix[34][30] = matrix[33][30] = matrix[32][30] = matrix[31][30] = matrix[30][30] = "#";

	matrix[28][5] = matrix[28][4] = matrix[28][6] = matrix[28][7] = matrix[29][7] = matrix[30][7] = matrix[31][7] = "#";
	matrix[28][37] = matrix[28][36] = matrix[28][35] = matrix[28][34] = matrix[29][34] = matrix[30][34] = matrix[31][34] = "#";

	matrix[26][11] = matrix[25][11] = matrix[24][11] = matrix[23][11] = matrix[22][11] = matrix[21][11] = matrix[20][11] = matrix[19][11] = matrix[18][11] = matrix[17][11] = matrix[16][11] = matrix[15][11] = "#";
	matrix[26][30] = matrix[25][30] = matrix[24][30] = matrix[23][30] = matrix[22][30] = matrix[21][30] = matrix[20][30] = matrix[19][30] = matrix[18][30] = matrix[17][30] = matrix[16][30] = matrix[15][30] = "#";

	//
}