#include <iostream>
#include <Windows.h>
#include <random>

using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

const int WIDTH = 21;
const int HEIGHT = 15;
const int LENGTH_SNAKE = (WIDTH - 3) * (HEIGHT - 2);

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

int snake_run = UP;

bool GameRun = true;

char snake = 'O';
char food = '*';

char map[] =
"####################\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"#                  #\n"
"####################\n";

int snake_x[LENGTH_SNAKE] = { 0 };
int snake_y[LENGTH_SNAKE] = { 0 };
int snake_len = 1;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist_w(1, WIDTH - 3);
uniform_int_distribution<> dist_h(1, HEIGHT - 2);

int food_x = dist_w(gen);
int food_y = dist_h(gen);

int main()
{
	snake_x[0] = WIDTH / 2;
	snake_y[0] = HEIGHT / 2;
	float timing = clock();

	while (GameRun)
	{
		if (GetKeyState('W') & 0x8000)
		{
			if (snake_run != DOWN)
			{
				snake_run = UP;
			}
		}
		if (GetKeyState('S') & 0x8000)
		{
			if (snake_run != UP)
			{
				snake_run = DOWN;
			}
		}
		if (GetKeyState('A') & 0x8000)
		{
			if (snake_run != RIGHT)
			{
				snake_run = LEFT;
			}
		}
		if (GetKeyState('D') & 0x8000)
		{
			if (snake_run != LEFT)
			{
				snake_run = RIGHT;
			}
		}

		if ((clock() - timing) / CLOCKS_PER_SEC >= 0.18)
		{
			timing = clock();

			if ((snake_x[0] == food_x) && (snake_y[0] == food_y))
			{
				snake_len++;
				food_x = dist_w(gen);
				food_y = dist_h(gen);
			}

			for (int i = snake_len - 2; i >= 0; --i)
			{
				snake_x[i + 1] = snake_x[i];
				snake_y[i + 1] = snake_y[i];
			}

			if (snake_run == UP)
			{
				--snake_y[0];
			}
			if (snake_run == DOWN)
			{
				++snake_y[0];
			}
			if (snake_run == LEFT)
			{
				--snake_x[0];
			}
			if (snake_run == RIGHT)
			{
				++snake_x[0];
			}

			if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1)
			{
				GameRun = false;
			}

			for (int i = 1; i < snake_len; i++)
			{
				if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
				{
					GameRun = false;
				}
			}

			gotoxy(0, 0);

			map[food_y * WIDTH + food_x] = food;

			for (int i = 0; i < snake_len; i++)
			{
				map[snake_y[i] * WIDTH + snake_x[i]] = snake;
			}
			cout << map;
			for (int i = 0; i < snake_len; i++)
			{
				map[snake_y[i] * WIDTH + snake_x[i]] = ' ';
			}
		}
	}
	if (snake_len == LENGTH_SNAKE)
	{
		cout << "YOU WIN";
		gotoxy(WIDTH, HEIGHT);
	}
	else
	{
		cout << "GAME OVER";
		gotoxy(WIDTH, HEIGHT);
	}
}