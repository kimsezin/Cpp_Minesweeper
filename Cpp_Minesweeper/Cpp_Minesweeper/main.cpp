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
pos tail[10000];
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
	for (int i = 1; i <= BOMBS; i++)//폭탄 개수만큼 폭탄 만들기
	{
		int x = rand() % LENGTH + 1; // +1한 이유는 1부터시작시키기위해
		int y = rand() % WIDTH + 1;
		if (x == a and y == b)
		{
			int x = rand() % LENGTH + 1; // 처음 누른곳이 폭탄이 설치되면 다시
			int y = rand() % WIDTH + 1;
		}
		board[x][y] = 9; // 이미지중 9번째인 폭탄모양
	}

} //완료

void numberGenerator()
{
	for (int i = 1; i <= LENGTH; i++) // 모든 타일 뒤져서
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			if (board[i][j] != 9) //폭탄이 아닌거
			{
				int noBombs = 0;
				if (board[i - 1][j - 1] == 9) //좌상
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9) // 좌
				{
					noBombs++;
				}
				if (board[i][j - 1] == 9) //좌하
				{
					noBombs++;
				}
				if (board[i + 1][j - 1] == 9)//우상
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)//우
				{
					noBombs++;
				}
				if (board[i + 1][j + 1] == 9)//우하
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)//하
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9)//상
				{
					noBombs++;
				}
				board[i][j] = noBombs;
			}
		}
	}
}
void verification0(int i, int j)
{
	user_board[i][j] = 0;
	//좌상
	if (board[i - 1][j - 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH &&j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j -1;
		ltail++;
	}
	//상
	if (board[i - 1][j] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j;
		ltail++;
	}
	//좌하
	if (board[i - 1][j + 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j + 1;
		ltail++;
	}
	//좌
	if (board[i][j - 1] == 0 && i > 0 && i <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j - 1;
		ltail++;
	}
	//우
	if (board[i][j + 1] == 0 && i > 0 && i <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j + 1;
		ltail++;
	}
	//우상
	if (board[i + 1][j - 1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j - 1;
		ltail++;
	}
	//하
	if (board[i + 1][j] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j;
		ltail++;
	}
	//우하
	if (board[i + 1][j+1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j + 1> 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j + 1;
		ltail++;
	}
}

void firstMoove(int i, int j)
{
	if (board[i][j] == 0) // 주변이 다 폭탄인거?? 이런 경우가있나..
	{
		user_board[i][j] = 0; // 유저보드에 옮기기
		verification0(i, j);
		while (excttail < ltail)
		{
			user_board[tail[excttail].column][tail[excttail].row] = 0;
			excttail++;
		}
	}
	else
	{
		user_board[i][j] = board[i][j];
	}
	if (board[i - 1][j - 1] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i - 1][j - 1] == 0)
		{
			user_board[i - 1][j - 1] = 0;
			verification0(i - 1, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j - 1] = board[i - 1][j - 1];
		}
	}
	if (board[i - 1][j] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		if (board[i - 1][j] == 0)
		{
			user_board[i - 1][j] = 0;
			verification0(i - 1, j);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j] = board[i - 1][j];
		}
	}
	if (board[i - 1][j + 1] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i - 1][j + 1] == 0)
		{
			user_board[i - 1][j + 1] = 0;
			verification0(i - 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j + 1] = board[i - 1][j + 1];
		}
	}
	if (board[i][j - 1] != 9 && i > 0 && i <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i][j - 1] == 0)
		{
			user_board[i][j - 1] = 0;
			verification0(i, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i][j - 1] = board[i][j - 1];
		}
	}
	if (board[i][j + 1] != 9 && i > 0 && i <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i][j + 1] == 0)
		{
			user_board[i][j + 1] = 0;
			verification0(i, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i][j + 1] = board[i][j + 1];
		}
	}
	if (board[i + 1][j - 1] != 9 && i + 1> 0 && i + 1<= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i + 1][j - 1] == 0)
		{
			user_board[i + 1][j - 1] = 0;
			verification0(i + 1, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i+ 1][j - 1] = board[i+ 1][j - 1];
		}
	}
	if (board[i + 1][j] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j  > 0 && j  <= WIDTH)
	{
		if (board[i + 1][j ] == 0)
		{
			user_board[i + 1][j ] = 0;
			verification0(i + 1, j );
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j ] = board[i + 1][j ];
		}
	}
	if (board[i + 1][j + 1] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i + 1][j + 1] == 0)
		{
			user_board[i + 1][j + 1] = 0;
			verification0(i + 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j + 1] = board[i + 1][j + 1];
		}
	}
	if (board[i - 1][j + 2] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i - 1][j + 2] == 0)
		{
			user_board[i - 1][j + 2] = 0;
			verification0(i - 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j + 2] = board[i - 1][j + 2];
		}
	}
	if (board[i][j + 2] != 9 && i  > 0 && i  <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i ][j + 2] == 0)
		{
			user_board[i][j + 2] = 0;
			verification0(i , j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i][j + 2] = board[i][j + 2];
		}
	}
	if (board[i + 1][j + 2] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i + 1][j + 2] == 0)
		{
			user_board[i + 1][j + 2] = 0;
			verification0(i + 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row];
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j + 2] = board[i + 1][j + 2];
		}
	}
}
int main()
{
	RenderWindow app(VideoMode(600, 570), "Minesweeper made by kimsezin"); //움직일거니까 videomode 

	Texture t;
	t.loadFromFile("images/tiles.jpg"); //tiles.jpg받아오기
	
	
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
		while (app.pollEvent(e)) // 이벤트가 발생할 경우
		{
			if (e.type == Event::Closed) // 닫는 이벤트
			{
				app.close(); // 앱 꺼주기
			}
			if (e.type == Event::MouseButtonPressed) // 마우스 버튼 눌렀을 시
			{
				if (e.key.code == Mouse::Left) // 왼쪽 마우스
				{
					if (firstMove == 0) // 맨 처음 누를때
					{
						bombsInitalisation(x,y); // 폭탄생성
						numberGenerator();//본인 주변 8개중 폭탄아닌거 개수 board에 설정 
						firstMoove(x, y);
						firstMove = 1;
					}
					else if (board[x][y] == 0)
					{
						verification0(x, y);
						while (excttail < ltail)
						{
							user_board[tail[excttail].column][tail[excttail].row] = 0;
							excttail++;
						}
					}
					else
					{
						user_board[x][y] = board[x][y];
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
		}
		app.clear(Color::White);
		if (bombsFound == BOMBS)
		{
			Sprite win(winSource);
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
						user_board[i][j] = board[i][j];
					}
					s.setTextureRect(IntRect(user_board[i][j] * w, 0, w, w));
					s.setPosition(i * w, j * w);
					app.draw(s); 
				}
			}
			app.display();
		}
	}

	return 0;
}