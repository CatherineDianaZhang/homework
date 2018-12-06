#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'

void snakeMove();//蛇的移动 
int gameover();//判断游戏是否结束 
void output();//输出蛇移动后的状态 


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

//蛇的身体和头部 
int snakeLength=5;
int snakeX[5]={1,2,3,4,5};
int snakeY[5]={1,1,1,1,1};


int main() {
    char ch;
    output();//输出初始状态
    while (1) {
        scanf(" %c", &ch);  
		snakeMove(); 
        switch (ch) {//四个键对应蛇头移动方向
        case 'w' :
            snakeY[4] -= 1;
            map[snakeY[4]][snakeX[4]] = 'H';
            break; 
        case 's' :
            snakeY[4] += 1;
            map[snakeY[4]][snakeX[4]] = 'H';
            break;
        case 'a' :
            snakeX[4] -= 1;
            map[snakeY[4]][snakeX[4]] = 'H';
            break;
        case 'd' :
            snakeX[4] += 1;
            map[snakeY[4]][snakeX[4]] = 'H';
            break;
    	}
        if (!gameover()) {
            printf("gameover\n");
        } 
		else {
			system("cls");//刷新界面
            output();
    	}
    }
}

//蛇的移动，将最后一节身体设置为空，头部设置为身体
void snakeMove() {
    int i;
    map[snakeY[0]][snakeX[0]] = ' ';
    for (i = 0; i < 4; i++) {
        snakeX[i] = snakeX[i + 1];
        snakeY[i] = snakeY[i + 1];
        map[snakeY[i]][snakeX[i]] = 'X';
    }
}

int gameover() {
    if (snakeX[4] == 10 || snakeX[4] == 0) {
        return 0;
    }
    if (snakeY[4] == 10 || snakeY[4] == 0) {
        return 0;
    }//蛇头碰到边界，游戏结束
    int i;
    for (i = 0; i < 4; i++) {
        if (snakeX[4] == snakeX[i] && snakeY[4] == snakeY[i]) {
            return 0;
        }
    }//蛇头碰到身体，游戏结束
    return 1;
}

//输出新的状态
void output() {
	int i,j;
    for (i = 0; i <= 11; i++) {
        for (j = 0; j <= 11; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

