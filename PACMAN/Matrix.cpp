#include "Matrix.hpp"

Matrix::Matrix(){}

Matrix::~Matrix(){}

void Matrix::Setup_Matrix(std::vector<std::vector<std::string>>& matrix)
{
	//Walls

	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			matrix[height][width] = " ";
	}

	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height == 5 && width >= 0 && width <= 42)
				matrix[height][width] = "#1";
	}
	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height > 5 && (width == 0 || width == 41) && height <= 39)
				matrix[height][width] = "#5";
	}
	for (int height = 0; height < 42; ++height)
	{
		for (int width = 0; width < 42; ++width)
			if (height == 40 && width >= 0 && width <= 42)
				matrix[height][width] = "#1";
	}

	//I dont give a fuck what is that

	matrix[21][0] = matrix[22][0] = matrix[23][0] = matrix[21][41] = matrix[22][41] = matrix[23][41] = "";

	//Walls

	matrix[26][16] = matrix[26][17] = matrix[26][18] = matrix[26][19] = matrix[26][20] = matrix[26][21] = matrix[26][22] = matrix[26][23] = matrix[26][24] = matrix[26][25] = matrix[22][24] = matrix[22][25] = matrix[22][16] = matrix[22][17] = matrix[28][36] = matrix[28][35] = matrix[36][29] = matrix[36][28] = matrix[36][27] = matrix[36][26] = matrix[36][34] = matrix[36][33] = matrix[36][32] = matrix[36][31] = matrix[36][36] = matrix[36][35] = matrix[36][12] = matrix[36][13] = matrix[36][14] = matrix[36][15] = matrix[36][9] = matrix[36][10] = matrix[36][5] = matrix[36][6] = matrix[36][7] = matrix[36][8] = matrix[28][5] = matrix[28][6] = matrix[32][40] = matrix[32][39] = matrix[32][1] = matrix[32][2] = matrix[24][41] = matrix[24][40] = matrix[24][39] = matrix[24][38] = matrix[24][37] = matrix[24][36] = matrix[24][35] = matrix[24][1] = matrix[24][2] = matrix[24][3] = matrix[24][4] = matrix[24][5] = matrix[24][6] = matrix[20][1] = matrix[20][2] = matrix[20][3] = matrix[20][4] = matrix[20][5] = matrix[20][6] = matrix[20][41] = matrix[20][40] = matrix[20][39] = matrix[20][38] = matrix[20][37] = matrix[20][36] = matrix[20][35] = "#1";
	matrix[5][0] = matrix[24][0] = matrix[28][34] = matrix[22][15] = "#2";
	matrix[15][22] = matrix[15][23] = matrix[15][24] = matrix[15][25] = matrix[15][19] = matrix[15][18] = matrix[15][17] = matrix[15][16] = matrix[15][21] = matrix[15][20] = matrix[30][16] = matrix[30][17] = matrix[30][18] = matrix[30][19] = matrix[30][20] = matrix[30][21] = matrix[30][22] = matrix[30][23] = matrix[30][24] = matrix[30][25] = matrix[15][36] = matrix[15][35] = matrix[15][5] = matrix[15][6] = matrix[9][29] = matrix[9][28] = matrix[9][27] = matrix[9][26] = matrix[9][13] = matrix[9][14] = matrix[9][15] = matrix[9][12] = matrix[5][20] = matrix[5][21] = matrix[9][5] = matrix[9][6] = matrix[9][36] = matrix[9][35] = matrix[9][34] = "#3";
	matrix[5][41] = matrix[24][41] = matrix[28][7] = matrix[22][26] = "#4";
	matrix[23][26] = matrix[24][26] = matrix[25][26] = matrix[25][15] = matrix[24][15] = matrix[23][15] = matrix[35][30] = matrix[34][30] = matrix[33][30] = matrix[32][30] = matrix[31][30] = matrix[35][11] = matrix[34][11] = matrix[33][11] = matrix[32][11] = matrix[31][11] = matrix[25][30] = matrix[24][30] = matrix[23][30] = matrix[22][30] = matrix[21][30] = matrix[20][30] = matrix[19][30] = matrix[18][30] = matrix[17][30] = matrix[16][30] = matrix[25][11] = matrix[24][11] = matrix[23][11] = matrix[22][11] = matrix[21][11] = matrix[20][11] = matrix[19][11] = matrix[18][11] = matrix[17][11] = matrix[16][11] = matrix[29][7] = matrix[30][7] = matrix[31][7] = matrix[29][34] = matrix[30][34] = matrix[31][34] = "#5";
	matrix[20][0] = matrix[40][0] = matrix[26][15] = "#6";
	matrix[20][41] = matrix[40][41] = matrix[26][26] = "#7";
	matrix[6][20] =  "#8";
	matrix[35][20] = matrix[34][20] = matrix[10][25] = matrix[7][20] = matrix[8][20] = matrix[9][20] = matrix[10][20] = matrix[10][4] = matrix[10][34] = matrix[10][11] = matrix[31][15] = "#9";
	matrix[11][20] = "#10";
	matrix[11][21] = "#11";
	matrix[34][21] = matrix[35][21] = matrix[10][30] = matrix[10][16] = matrix[7][21] = matrix[8][21] = matrix[9][21] = matrix[10][21] = matrix[10][7] = matrix[10][37] = matrix[31][26] = "#12";
	matrix[6][21] = "#13";
	matrix[20][7] = matrix[24][7] = matrix[32][3] = matrix[28][37] = matrix[36][16] = matrix[36][37] = matrix[22][18] = "#14";
	matrix[20][34] = matrix[24][34] = matrix[32][38] = matrix[36][4] = matrix[36][25] = matrix[28][4] = matrix[22][23] = "#15";
	matrix[32][0] = "#16";
	matrix[32][41] = "#17";
	matrix[15][15] = matrix[9][4] = matrix[9][34] = matrix[9][11] = matrix[9][25] = matrix[15][4] = matrix[15][34] = matrix[30][15] = "#18";
	matrix[15][26] = matrix[9][7] = matrix[9][37] = matrix[9][16] = matrix[9][30] = matrix[15][7] = matrix[15][37] = matrix[30][26] = "#19";
	matrix[16][22] = matrix[16][23] = matrix[16][24] = matrix[16][25] = matrix[16][19] = matrix[16][18] = matrix[16][17] = matrix[16][16] = matrix[32][22] = matrix[32][23] = matrix[32][24] = matrix[32][25] = matrix[32][16] = matrix[32][17] = matrix[32][18] = matrix[32][19] = matrix[16][36] = matrix[16][35] = matrix[16][5] = matrix[16][6] = matrix[11][29] = matrix[11][28] = matrix[11][27] = matrix[11][26] = matrix[11][12] = matrix[11][13] = matrix[11][14] = matrix[11][15] = matrix[11][5] = matrix[11][6] = matrix[11][36] = matrix[11][35] = matrix[11][34] = "#20";
	matrix[16][15] = matrix[11][4] = matrix[11][34] = matrix[11][11] = matrix[11][25] = matrix[16][4] = matrix[16][34] = matrix[32][15] = "#21";
	matrix[16][26] = matrix[18][21] = matrix[36][21] = matrix[11][7] = matrix[11][37] = matrix[11][16] = matrix[11][30] = matrix[16][7] = matrix[16][37] = matrix[32][26] = "#22";
	matrix[30][11] = matrix[30][30] = matrix[15][11] = matrix[15][30] = "#23";
	matrix[26][11] = matrix[32][7] = matrix[26][30] = matrix[32][34] = "#24";
	matrix[36][11] = matrix[36][30] = "#25";
	matrix[33][20] = "#26";
	matrix[33][21] = "#27";
	matrix[36][20] = matrix[18][20] = "#28";
	matrix[17][20] = "#29";
	matrix[17][21] = "#30";

	// Points

	matrix[7][2] = matrix[7][4] = matrix[7][6] = matrix[7][8] = matrix[7][10] = matrix[7][12] = matrix[7][14] = matrix[7][16] = matrix[7][18] = "*";
	matrix[7][23] = matrix[7][25] = matrix[7][27] = matrix[7][29] = matrix[7][31] = matrix[7][33] = matrix[7][35] = matrix[7][37] = matrix[7][39] = "*";
	matrix[13][2] = matrix[13][4] = matrix[13][6] = matrix[13][8] = matrix[13][10] = matrix[13][12] = matrix[13][14] = matrix[13][16] = matrix[13][18] = matrix[13][20] = matrix[13][22] = matrix[13][24] = matrix[13][26] = matrix[13][28] = matrix[13][30] = matrix[13][32] = matrix[13][34] = matrix[13][36] = matrix[13][39] = "*";
	matrix[9][2] = matrix[9][9] = matrix[9][18] = matrix[11][2] = matrix[11][9] = matrix[11][18] = "*";
	matrix[9][23] = matrix[9][32] = matrix[9][39] = matrix[11][23] = matrix[11][32] = matrix[11][39] = "*";
	matrix[15][2] = matrix[15][9] = matrix[18][2] = matrix[18][9] = matrix[18][4] = matrix[18][6] = "*";
	matrix[15][39] = matrix[15][32] = matrix[18][39] = matrix[18][32] = matrix[18][37] = matrix[18][35] = "*";
	matrix[20][9] = matrix[22][9] = matrix[24][9] = matrix[26][9] = matrix[28][9] = matrix[30][9] = matrix[32][9] = matrix[34][9] = "*";
	matrix[20][32] = matrix[22][32] = matrix[24][32] = matrix[26][32] = matrix[28][32] = matrix[30][32] = matrix[32][32] = matrix[34][32] = "*";
	matrix[38][2] = matrix[38][6] = matrix[38][8] = matrix[38][10] = matrix[38][12] = matrix[38][14] = matrix[38][16] = matrix[38][18] = matrix[38][23] = matrix[38][25] = matrix[38][27] = matrix[38][29] = matrix[38][31] = matrix[38][33] = matrix[38][37] = matrix[38][39] = "*";
	matrix[26][7] = matrix[26][5] = matrix[26][3] = matrix[28][2] = matrix[30][2] = matrix[30][4] = matrix[32][5] = matrix[34][5] = matrix[34][7] = matrix[34][2] = matrix[36][2] = "*";
	matrix[26][34] = matrix[26][36] = matrix[26][38] = matrix[28][39] = matrix[30][39] = matrix[32][36] = matrix[34][35] = matrix[34][37] = matrix[34][39] = matrix[36][39] = matrix[30][37] =  "*";
	matrix[36][18] = matrix[34][18] = matrix[34][16] = matrix[34][13] = matrix[32][13] = matrix[30][13] = "*";
	matrix[36][23] = matrix[34][23] = matrix[34][25] = matrix[34][28] = matrix[32][28] = matrix[30][28] = "*";
	matrix[38][35] = matrix[38][4] = "*";
	
	//Tablets

	matrix[30][2] = matrix[30][39] = matrix[7][2] = matrix[7][39] = "*P";

	//
	matrix[2][25] = "N2_1";
	matrix[2][27] = "N2_2";
	matrix[2][29] = "N2_3";
	matrix[2][31] = "N2_4";
	matrix[2][33] = "N2_5";
	matrix[2][35] = "N2_6";
}
