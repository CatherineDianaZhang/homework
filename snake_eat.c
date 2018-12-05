#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void snakeMove(int,int);//蛇移动 
void put_money(void);//放置食物 
void output(void);//输出字符矩阵 
int judge(void);//判断游戏是否结束 
void snakeExtent(void);//蛇吃食物后伸长 

//初始状态 
char map[12][12] = {"************",
                    "*XXXXH     *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "*          *",
                    "************"
					};

//蛇身和蛇头的坐标，snakeX[0]和snakeY[o]为蛇头 
int snakeX[SNAKE_MAX_LENGTH]={5,4,3,2,1};
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};
int snakeLength=5;
int moneyX,moneyY;

int judge() {
	int i;
	if(snakeX[0] == 0 || snakeX[0] == 11 || snakeY[0] == 0 || snakeY[0] == 11)
		return 0;
	//碰到墙壁游戏结束 
	for(i = 1; i < snakeLength; ++ i) {
		if(snakeX[0] == snakeX[i]&&snakeY[0] == snakeY[i])
			return 0;
	} 
	//碰到自己游戏结束 
	return 1;
}

void output() {
	int i ,j;
	for(int i = 0; i < 12; i ++) {
		for(j = 0; j < 12; j ++)
			printf("%c",map[i][j]);
		printf("\n");
	}
}

void  put_money() {
	//随机放置食物 
	int moneyX = rand() % 9;
	int moneyY = rand() % 9; 
	//判断位置是否为空 
	if(map[moneyX][moneyY] == BLANK_CELL) {
		map[moneyX][moneyY] == SNAKE_FOOD;
	} 
	else put_money();//不为空则调用自己 
}

void snakeMove(int x,int y) {
	
	int i;
	if(snakeX[0] + x == moneyX && snakeY[0] + y == moneyY)
		snakeExtent();
	else map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = BLANK_CELL;
	//蛇向前走，后面一段继承前面一段的位置 
	for(i = snakeLength -1;i > 0; i --); {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
		map[snakeY[i]][snakeX[i]] = SNAKE_BODY;
	}
	snakeX[0] += x;
	snakeY[0] += y;
	map[snakeY[0]][snakeX[0]] = SNAKE_HEAD;
	output();
}

void snakeExtent() {//蛇头碰到食物就伸长 
	if(snakeLength < SNAKE_MAX_LENGTH) {
		snakeY[snakeLength] = snakeY[snakeLength - 1];
		snakeX[snakeLength] = snakeX[snakeLength - 1];
		snakeLength ++ ;
	}//判断蛇长度是否小于最长长度，若是，则伸长 
	else map[snakeY[snakeLength-1]][snakeX[snakeLength-1]];
} 


int main() { 	
	char ch;			
	output();//输出初始状态	
	put_money();
	while(judge()) {//判断游戏是否结束，若未结束，则进行移动 
		scanf("%c",&ch);				
		switch(ch) {	//ASDW分别代表的移动方向		
			case 'A': 				
				snakeMove (-1, 0);				
				break;			
			case 'S':				
				snakeMove (0, 1);				
				break;			
			case 'D':				
				snakeMove (1, 0);				
				break; 			
			case 'W':				
				snakeMove (0, -1);			
				break;			
		}
		if(moneyX[0] == snakeX[0] && moneyY[0] == snakeY[0])
			snakeExtent();
		system("cls");
		output();	//输出移动后状态	
	}
	printf("%s","Came Over!!!");
}
