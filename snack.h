//定义范围
#define WIDE 60
#define HIGH 20

//单位坐标
struct BODY
{
	int X;
	int Y;
};

//蛇的模型
struct SNAKE
{
	int size;
	struct BODY body[WIDE * HIGH];
}snake;

int food[2] = { 0 };    // food[0] 表示X轴 food[1] 表示Y轴
int score = 0;

//偏移坐标
int dx = 0;
int dy = 0;

//记录蛇最后一节的坐标
int lx = 0;
int ly = 0;

//函数申明
void inItFood();
void inItSnake();
void ShowUI();
void PlayGame();
void inItWall();
