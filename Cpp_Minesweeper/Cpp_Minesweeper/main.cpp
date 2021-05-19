#include <SFML/Graphics.hpp>

#define LENGTH 16
#define WIDTH 16
#define BOMBS 40

using namespace sf;
using namespace std;

struct pos
{
	int row;
	int column;
};

int w = 32; // image pixel length
int board[LENGTH + 1][WIDTH + 1];
int user_board[LENGTH + 1][WIDTH + 1];
int tail[10000];
int ltail, excttail, firstMove, bombsFound;

void initialisationUserBoard()
{
	for (int i = 1; i <= LENGTH; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			user_board[i][j] = 10;
		}
	}
}

void bombsInitalisation(int a, int b) // a,b are the coordnates of the first move
{
	for (int i = 1; i <= BOMBS; i++)
	{
		int x = rand() % LENGTH + 1;
		int y = rand() % WIDTH + 1;
		if (x == a and y == b)
		{
			int x = rand() % LENGTH + 1;
			int y = rand() % WIDTH + 1;
		}
		board[x][y] = 9;
	}

}

void numberGenerator()
{
	for (int i = 1; i <= LENGTH; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			if (board[i][j] != 9)
			{
				int noBombs = 0;
				if (board[i - 1][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9)
				{
					noBombs++;
				}
				if (board[i][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i][j] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j + 1] == 9)
				{
					noBombs++;
				}
				board[i][j] = noBombs;
			}
		}
	}
}
int main()
{
	RenderWindow app(VideoMode(600, 570), "Minesweeper made by kimsezin");

	Texture t;
	t.loadFromFile("images/tiles.jpg");
	
	
	Texture winSource;
	winSource.loadFromFile("images/win.jpg");
	
	Sprite s(t);
	initialisationUserBoard();

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}
		}


		if (e.type == Event::MouseButtonPressed)
		{
			if (e.key.code == Mouse::Left)
			{
				if (firstMove == 0)
				{
					bombsInitalisation(x, y);
					numberGenerator();
					firstMove = 1;
				}
			}
			else if (e.key.code == Mouse::Right)
			{
				if (user_board[x][x] == 11)
				{
					user_board[x][y] = 10;
				}
				else if (user_board[x][y] > 9)
				{
					user_board[x][y] = 11;
				}
				if (board[x][y] == 9)
				{
					bombsFound++;
				}
			}
		}
		app.clear(Color::White);
		if (bombsFound == BOMBS)
		{
			Sprite win;
			win.setTexture(winSource);
			app.draw(win);
			app.display();
		}
		else
		{
			for (int i = 1; i <= LENGTH; i++)
			{
				for (int j = 1; j <= WIDTH; j++)
				{
					if (user_board[x][y] == 9)
					{
						user_board[i][j] == board[i][j];
					}
					s.setTextureRect(IntRect(user_board[i][j] * w, 0, w, w));
					s.setPosition(i * w, j * w);
					app.draw(s);
				}
			}
		}
	}

	return 0;
}