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
	for (int i = 1; i <= BOMBS; i++)//��ź ������ŭ ��ź �����
	{
		int x = rand() % LENGTH + 1; // +1�� ������ 1���ͽ��۽�Ű������
		int y = rand() % WIDTH + 1;
		if (x == a and y == b)
		{
			int x = rand() % LENGTH + 1; // ó�� �������� ��ź�� ��ġ�Ǹ� �ٽ�
			int y = rand() % WIDTH + 1;
		}
		board[x][y] = 9; // �̹����� 9��°�� ��ź���
	}

} //�Ϸ�

void numberGenerator()
{
	for (int i = 1; i <= LENGTH; i++) // ��� Ÿ�� ������
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			if (board[i][j] != 9) //��ź�� �ƴѰ�
			{
				int noBombs = 0;
				if (board[i - 1][j - 1] == 9) //�»�
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9) // ��
				{
					noBombs++;
				}
				if (board[i][j - 1] == 9) //����
				{
					noBombs++;
				}
				if (board[i + 1][j - 1] == 9)//���
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)//��
				{
					noBombs++;
				}
				if (board[i + 1][j + 1] == 9)//����
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)//��
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9)//��
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
	//�»�
	if (board[i - 1][j - 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH &&j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j -1;
		ltail++;
	}
	//��
	if (board[i - 1][j] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j;
		ltail++;
	}
	//����
	if (board[i - 1][j + 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j + 1;
		ltail++;
	}
	//��
	if (board[i][j - 1] == 0 && i > 0 && i <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j - 1;
		ltail++;
	}
	//��
	if (board[i][j + 1] == 0 && i > 0 && i <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j + 1;
		ltail++;
	}
	//���
	if (board[i + 1][j - 1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j - 1;
		ltail++;
	}
	//��
	if (board[i + 1][j] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j;
		ltail++;
	}
	//����
	if (board[i + 1][j+1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j + 1> 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j + 1;
		ltail++;
	}
}

void firstMoove(int i, int j)
{
	if (board[i][j] == 0) // �ֺ��� �� ��ź�ΰ�?? �̷� ��찡�ֳ�..
	{
		user_board[i][j] = 0; // �������忡 �ű��
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
	RenderWindow app(VideoMode(600, 570), "Minesweeper made by kimsezin"); //�����ϰŴϱ� videomode 

	Texture t;
	t.loadFromFile("images/tiles.jpg"); //tiles.jpg�޾ƿ���
	
	
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
		while (app.pollEvent(e)) // �̺�Ʈ�� �߻��� ���
		{
			if (e.type == Event::Closed) // �ݴ� �̺�Ʈ
			{
				app.close(); // �� ���ֱ�
			}
			if (e.type == Event::MouseButtonPressed) // ���콺 ��ư ������ ��
			{
				if (e.key.code == Mouse::Left) // ���� ���콺
				{
					if (firstMove == 0) // �� ó�� ������
					{
						bombsInitalisation(x,y); // ��ź����
						numberGenerator();//���� �ֺ� 8���� ��ź�ƴѰ� ���� board�� ���� 
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