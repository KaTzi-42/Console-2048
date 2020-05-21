#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "menu.h"
const int SIZEM = 4;
//чи залишились ще пусті ячейки 
bool IsEmpty(int** matrix)
{
	for (size_t i = 0; i < SIZEM; i++)
		for (size_t j = 0; j < SIZEM; j++)
			if (!matrix[i][j])
				return false;
	return true;
}
bool GameOver(int** matrix)
{
	for (int i = 0; i < SIZEM; i++)
		for (int j = 0; j < SIZEM - 1; j++)
			if (matrix[i][j] == matrix[i][j + 1])
				return false;
	for (int i = 0; i < SIZEM; i++)
		for (int j = 0; j < SIZEM - 1; j++)
			if (matrix[j][i] == matrix[j + 1][i])
				return false;

	return true;
}
bool Win(int** matrix)
{
	for (int i = 0; i < SIZEM; i++)
		for (int j = 0; j < SIZEM; j++)
			if (matrix[i][j] == 2048)
				return true;
	return false;
}

void Top()
{
	for (size_t i = 0; i < SIZEM + 1; i++)
		printf_s("%c", char(205));
	printf_s("%c", 203);
}
void Center()
{
	for (size_t j = 0; j < SIZEM; j++)
	{
		for (size_t i = 0; i < SIZEM + 1; i++)
			printf_s("%c", 205);
		printf_s("%c", 206);
	}
}
void Bottom()
{
	printf_s("%c", 200);
	for (size_t j = 0; j < SIZEM; j++)
	{
		for (size_t i = 0; i < SIZEM + 1; i++)
			printf_s("%c", 205);
		printf_s("%c", 202);
	}
}
void Print(int** matrix)
{
	int pos = 1;
	system("cls");
	if (Win(matrix))
	{
		Gotorc(TOP - 1, LEFT + 9);
		printf_s("%s", "VICTORY!");
	}
	else if (IsEmpty(matrix) && GameOver(matrix))
	{
		Gotorc(TOP - 1, LEFT + 9);
		printf_s("%s", "GAME OVER!");
	}
	Gotorc(TOP, LEFT);
	printf_s("%c", char(201));
	for (size_t j = 0; j < SIZEM; j++)
		Top();
	printf_s("\b%c", 187);
	for (size_t i = 0; i < SIZEM; i++)
	{
		Gotorc(TOP + (pos)+i, LEFT + 1);
		for (size_t j = 0; j < SIZEM; j++)
		{
			printf_s("\b%c%6c", 186, 186);
		}
		Gotorc(TOP + (++pos) + i, LEFT);
		printf_s("%c", 186);
		for (size_t j = 0; j < SIZEM; j++)
		{
			switch (matrix[i][j])
			{
			case 2:
				Paint(Black, White);
				printf_s("%4d%2c", matrix[i][j], 186);
				break;
			case 4:
				Paint(Black, DarkGray);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 8:
				Paint(Black, LightCyan);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 16:
				Paint(Black, Cyan);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 32:
				Paint(Black, LightBlue);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 64:
				Paint(Black, Blue);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 128:
				Paint(Black, Yellow);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 256:
				Paint(Black, LightMagenta);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 512:
				Paint(Black, Red);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 1024:
				Paint(Black, Green);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			case 2048:
				Paint(Black, Magenta);
				printf_s("%4d", matrix[i][j]);
				Paint(Black, White);
				printf_s("%2c", 186);
				break;
			default:
				printf_s("%6c", 186);
				break;
			}
		}
		Gotorc(TOP + (++pos) + i, LEFT);
		printf_s("%c", 204);
		Center();
		printf_s("\b%c", 185);
		if (i == SIZEM - 1)
		{
			Gotorc(TOP + pos + (SIZEM - 1), LEFT);
			Bottom();
			printf_s("\b%c", 188);
		}
	}
}
void PrintScore(char* name, int score)
{
	Gotorc(TOP, LEFT + 20);
	printf_s("\t%s", name);
	Gotorc(TOP + 1, LEFT + 20);
	printf_s("\t%s%d", "Score:", score);
}

bool Rnd(int** matrix, int start = 0, int finish = 4)
{
	srand(time(0));
	int x = 0, y = 0;
	int rnd = start + rand() % (finish + 1);
	if (!IsEmpty(matrix))
	{
		do
		{
			x = start + rand() % finish;
			y = start + rand() % finish;
		} while (matrix[x][y]);
		rnd < 4 ? matrix[x][y] = 2 : matrix[x][y] = 4;
		return true;
	}
	else
		return false;
}

void GoDown(int** matrix, int& score, int& swapCheck)
{
	swapCheck = 0;
	for (int i = 0; i < SIZEM; i++)
		for (int j = SIZEM - 1; j > 0; j--)
			if (matrix[j][i])
				for (int k = j - 1; k >= 0; k--)
					if ((matrix[k][i]) && matrix[k][i] == matrix[j][i])
					{
						matrix[j][i] <<= 1;
						matrix[k][i] = 0;
						score += matrix[j][i];
						swapCheck = 1;
						break;
					}
					else if (matrix[k][i])
						break;

	for (int i = 0; i < SIZEM; i++)
		for (int j = SIZEM - 1; j >= 0; j--)
			if (matrix[j][i])
				for (int k = j + 1; k < SIZEM; k++)
					if (!matrix[k][i])
					{
						swap(matrix[j++][i], matrix[k][i]);
						swapCheck = 1;
					}
					else break;
}

void GoUp(int** matrix, int& score, int& swapCheck)
{
	swapCheck = 0;
	for (int i = 0; i < SIZEM; i++)
		for (int j = 1; j < SIZEM; j++)
			if (matrix[j][i])
				for (int k = j - 1; k >= 0; k--)
					if ((matrix[k][i]) && matrix[k][i] == matrix[j][i])
					{
						matrix[k][i] <<= 1;
						matrix[j][i] = 0;
						score += matrix[k][i];
						swapCheck = 1;
						break;
					}
					else if (matrix[k][i])
						break;

	for (int i = 0; i < SIZEM; i++)
		for (int j = 1; j < SIZEM; j++)
			if (matrix[j][i])
				for (int k = j - 1; k >= 0; k--)
					if (!matrix[k][i])
					{
						swap(matrix[j--][i], matrix[k][i]);
						swapCheck = 1;
					}
					else break;
}

void GoRight(int** matrix, int& score, int& swapCheck)
{
	swapCheck = 0;
	for (int i = 0; i < SIZEM; i++)
		for (int j = SIZEM - 1; j > 0; j--)
			if (matrix[i][j])
				for (int k = j - 1; k >= 0; k--)
					if ((matrix[i][k]) && matrix[i][k] == matrix[i][j])
					{
						matrix[i][j] <<= 1;
						matrix[i][k] = 0;
						score += matrix[i][j];
						swapCheck = 1;
						break;
					}
					else if (matrix[i][k])
						break;

	for (int i = 0; i < SIZEM; i++)
		for (int j = SIZEM - 1; j >= 0; j--)
			if (matrix[i][j])
				for (int k = j + 1; k < SIZEM; k++)
					if (!matrix[i][k])
					{
						swap(matrix[i][j++], matrix[i][k]);
						swapCheck = 1;
					}
					else break;
}
void GoLeft(int** matrix, int& score, int& swapCheck)
{
	swapCheck = 0;
	for (int i = 0; i < SIZEM; i++)
		for (int j = 0; j < SIZEM; j++)
			if (matrix[i][j])
				for (int k = j + 1; k < SIZEM; k++)
					if (matrix[i][k] && matrix[i][k] == matrix[i][j])
					{
						matrix[i][j] <<= 1;
						matrix[i][k] = 0;
						score += matrix[i][j];
						swapCheck = 1;
						break;
					}
					else if (matrix[i][k])
						break;

	for (int i = 0; i < SIZEM; i++)
	{
		for (int j = 1; j < SIZEM; j++)
		{
			if (matrix[i][j])
				for (int k = j - 1; k >= 0; k--)
					if (!matrix[i][k])
					{
						swap(matrix[i][j--], matrix[i][k]);
						swapCheck = 1;
					}
					else break;
		}
	}
}
void NewGame(int**& matrix)
{
	int** temp = new int* [SIZEM];
	for (int i = 0; i < SIZEM; i++)
		temp[i] = new int[SIZEM] {0};
	Rnd(temp);
	Rnd(temp);
	delete[] matrix;
	matrix = temp;
}

int MenuNewGame(int** matrix, int ind = 0)
{
	printf_s("%s", "Start new game?");
	const char* ch[] = { "Start new game", "Top scores", "Exit" };
	int size = sizeof(ch) / sizeof(*ch);
	while (true)
	{
		Print(matrix);
		for (int i = 0; i < size; i++)
		{
			printf_s(i == ind ? "\n\t\t =>" : "\n\t\t  ");
			printf_s("%s", ch[i]);
		}
		char c = _getch();
		switch (c)
		{
		case 80:
			ind++;
			if (ind == size) ind = 0;
			break;
		case 72:
			if (ind == 0) ind = size;
			ind--;
			break;
		case 13:
			return ind;
		}
	}
}

void DelScore(Player*& gamer, int& size, int pos = 0)
{
	Player* temp = new Player[--size];
	for (size_t i = 0; i < size; i++)
		if (i >= pos)
			temp[i] = gamer[i + 1];
		else
			temp[i] = gamer[i];
	delete[] gamer;
	gamer = temp;
}

void SortScore(Player*& gamer, int size)
{
	int d = size / 2;
	while (d)
	{
		for (int i = d; i < size; i++)
		{
			Player temp = gamer[i];
			int j = i;
			while (j >= d && temp.score > gamer[j - d].score)
			{
				gamer[j] = gamer[j - d];
				j -= d;
			}
			gamer[j] = temp;
		}
		d /= 2;
	}
}

Player* SaveScore(char* name, int score, int& size)
{
	size = 0;
	char cc[100]{ 0 };
	int i = 0;
	FILE* scoreboard = NULL;
	int error = fopen_s(&scoreboard, "scboard.txt", "a+");
	if (error) {
		cout << "Error create the file";
		return nullptr;
	}
	while ((fgets(cc, 100, scoreboard)) != NULL)
		size++;
	size /= 2;
	Player* nGamer = new Player[++size]{};
	strcpy_s(nGamer[i].nick, name);
	nGamer[i].score = score;
	if (size > 1) {
		rewind(scoreboard);
		while (i++, !feof(scoreboard))
		{
			fgets(cc, 100, scoreboard);
			strcpy_s(nGamer[i].nick, cc);
			nGamer[i].nick[strlen(nGamer[i].nick) - 1] = 0;
			fscanf_s(scoreboard, "\n%d", &nGamer[i].score);
			fgets(cc, 100, scoreboard);
		}
	}
	fclose(scoreboard);

	for (i = 1; i < size; i++)
	{
		if (strcmp(name, nGamer[i].nick) == 0)
			if (score > nGamer[i].score)
			{
				DelScore(nGamer, size, i);
				break;
			}
			else
			{
				DelScore(nGamer, size);
				break;
			}
	}
	SortScore(nGamer, size);
	fopen_s(&scoreboard, "scboard.txt", "w");
	for (i = 0; i < size; i++)
	{
		fprintf_s(scoreboard, "%s\n", nGamer[i].nick);
		if (i == size - 1)
			fprintf_s(scoreboard, "%d", nGamer[i].score);
		else
			fprintf_s(scoreboard, "%d\n", nGamer[i].score);
	}
	fclose(scoreboard);

	return nGamer;
}

void PrintBoard(Player* score, int size)
{
	system("cls");
	Gotorc(TOP, LEFT);
	cout << "TOP SCORE";
	for (size_t i = 0; i < size; i++)
	{
		Gotorc(TOP + 1 + i, LEFT);
		cout << 1 + i << ')' << score[i].nick;
		Gotorc(TOP + 1 + i, LEFT + 20);
		cout << score[i].score;
	}
}
void NewScreen(int**& matrix, int& score, char* name)
{
	Player* sboard;
	int c = 0, sizeScore = 0;
	sboard = SaveScore(name, score, sizeScore);
	while (true)
	{
		c = MenuNewGame(matrix, c);
		switch (c)
		{
		case 0:
			NewGame(matrix);
			score = 0;
			Print(matrix);
			PrintScore(name, score);
			delete[] sboard;
			return;
		case 1:
			PrintBoard(sboard, sizeScore);
			break;
		case 2:
			delete[] sboard;
			exit(0);
			break;
		}
		cout << "\n\n\t\tPress any key...";
		_getch();
	}
}


int main()
{
	Shrift(20);
	int** matrix = new int* [SIZEM];
	for (int i = 0; i < SIZEM; i++)
		matrix[i] = new int[SIZEM] {0};
	Rnd(matrix);
	Rnd(matrix);
	int score = 0, swapCheck = 0;
	char c = 0;
	Player gamer{};
	cout << "\n\tYour nickname:";
	cin.getline(gamer.nick, 100);
	Print(matrix);
	PrintScore(gamer.nick, gamer.score);
	while (true)
	{
		c = _getch();
		switch (c)
		{
		case 72: //up
			GoUp(matrix, gamer.score, swapCheck);
			if (swapCheck)
				Rnd(matrix);
			break;
		case 80: //down
			GoDown(matrix, gamer.score, swapCheck);
			if (swapCheck)
				Rnd(matrix);
			break;
		case 77: //right
			GoRight(matrix, gamer.score, swapCheck);
			if (swapCheck)
				Rnd(matrix);
			break;
		case 75: //left
			GoLeft(matrix, gamer.score, swapCheck);
			if (swapCheck)
				Rnd(matrix);
			break;
		case 27:
			NewScreen(matrix, gamer.score, gamer.nick);
			break;
		}
		if (Win(matrix))
			NewScreen(matrix, gamer.score, gamer.nick);
		else if (IsEmpty(matrix) && GameOver(matrix))
			NewScreen(matrix, gamer.score, gamer.nick);
		else
		{
			Print(matrix);
			PrintScore(gamer.nick, gamer.score);
		}
	}
	return 0;
}

