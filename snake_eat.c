#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void snakeMove();//蛇移动 
void put_money();//放置食物 
void output();//输出字符矩阵 
int gameover();//判断游戏是否结束 


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
int snakeX[10]={5,4,3,2,1};
int snakeY[10]={1,1,1,1,1};
int snakeLength=5;
int moneyX,moneyY;

int main() {
    put_money();
    char ch;
    output();
    while (1) {
        scanf(" %c", &ch);
        snakeMove();
        switch (ch) {
        	case 'w' :
            	snakeY[0] -= 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
        	case 's' :
            	snakeY[0] += 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
        	case 'a' :
            	snakeX[0] -= 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
        	case 'd' :
            	snakeX[0] += 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
    	}
    	if (snakeX[0] == moneyX && snakeY[0] == moneyY) {
            put_money();
            snakeLength++;
            snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
            snakeY[snakeLength - 1] = snakeY[snakeLength - 2];
            map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = 'X';
        }
        if (!gameover()) {
            printf("gameover\n");
        } 
		else {
			system("cls");
            output();
    	}
    }
}

void snakeMove() {
    int i;
    map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = ' ';
    for (i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
        map[snakeY[i]][snakeX[i]] = 'X';
    }
}

int gameover() {
    if (snakeX[0] == 10 || snakeX[0] == 0) {
        return 0;
    }
    if (snakeY[0] == 10 || snakeY[0] == 0) {
        return 0;
    }
    int i;
    for (i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            return 0;
        }
    }
    return 1;
}
void output() {
	int i,j;
    for (i = 0; i <= 11; i++) {
        for (j = 0; j <= 11; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
void put_money() {
    srand((unsigned)(time(NULL)));
    moneyX = rand() % 9 + 1;
    moneyY = rand() % 9 + 1;
    while (map[moneyY][moneyX] != ' ') {
        moneyX = rand() % 9 + 1;
        moneyY = rand() % 9 + 1;
    }
    map[moneyY][moneyX] = '$';
}

