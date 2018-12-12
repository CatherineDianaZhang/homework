# 智能蛇游戏设计及算法

刚开始做贪吃蛇的时候，真的不知道从何下手。后来根据老师的伪代码，一步步将贪吃蛇游戏的总体拆分成一个个小的功能块，分别写出功能块的函数，再将他们拼接到一起，才成了一个真正的贪吃蛇游戏。

---

## 问题

1、在写贪吃蛇的移动部分时没有break,导致每按一个向下键贪吃蛇头部的左边都会多一个H。

2、随机放置食物函数中不了解随机函数知识。

3、判断智能蛇下一步向哪个方向走的函数参考了网上的资源。

---
## 学习总结

贪吃蛇只是代码生涯中的一个简单游戏，但对于现在的我来说还是很难。

但是，不了解的知识就要及时上网查找并解决，以免拖的时间越长，留下的隐患越大。

在之后的学习过程中，只有主动学习，才能达到自己理想的高度。


---
## 最终游戏界面及代码


![](http://ww1.sinaimg.cn/large/006V6dRsgy1fy3orge096j303u0810sl.jpg)


```c
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
char whereGoNext(int Hx, int Hy, int Fx, int Fy);//判断下一步向哪个方向走 


//初始状态 
char map[12][12] = {"***********",
                    "*XXXXH    *",
                    "*         *",
                    "*         *",
                    "*         *",
                    "*  *****  *",
                    "*         *",
                    "*         *",
                    "*         *",
                    "*         *",
                    "*         *",
                    "***********"
					};



//蛇身和蛇头的坐标，snakeX[0]和snakeY[0]为蛇头 
int snakeX[10]={5,4,3,2,1};
int snakeY[10]={1,1,1,1,1};
int snakeLength=5;
int moneyX,moneyY;


int main() {
    put_money();//放置食物
    output();//输出初始状态
    while (1) {
        char ch = whereGoNext(snakeX[0],snakeY[0],snakeX[snakeLength-1],snakeY[snakeLength-1]);
        Sleep(100);
        snakeMove();
        switch (ch) {//对应四个键的蛇头移动方向
        	case 'w' :
            	snakeY[0] -= 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
            	break; 
        	case 's' :
            	snakeY[0] += 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
            	break;
        	case 'a' :
            	snakeX[0] -= 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
            	break;
        	case 'd' :
            	snakeX[0] += 1;
            	map[snakeY[0]][snakeX[0]] = 'H';
            	break;
    	}
    	if (snakeX[0] == moneyX && snakeY[0] == moneyY) {//如果蛇头遇到食物，则蛇身增长 
            put_money();
            snakeLength++;
            snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
            snakeY[snakeLength - 1] = snakeY[snakeLength - 2];
            map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = 'X';
        }
        if (!gameover()) {
            printf("gameover\n");
        } 
    	else if(snakeLength == 20) {
    		printf("You Win!!!");
    		break;
		}
		else {
			system("cls");//刷新界面
            output();//输出最新状态
    	}
    }
}



//蛇的移动，将最后一节设置为空，蛇头设置为蛇身
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
    }//蛇头碰到边界，游戏结束
    int i;
    for (i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            return 0;
        }
    }//蛇头碰到蛇身，游戏结束
    return 1;
}



//输出最新状态
void output() {
	int i,j;
    for (i = 0; i <= 11; i++) {
        for (j = 0; j <= 11; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}



//随机放置食物
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

//判断智能蛇下一步向哪个方向走 
char whereGoNext(int Hx, int Hy, int Fx, int Fy) {
    int i;
    int temp = 0;
    int min = 10000;
    char moveble[5] = "WASD";
    int distance[4]={0, 0, 0, 0};
    distance[0] = abs(Fx - (Hx - 1)) + abs(Fy - Hy);
    distance[1] = abs(Fx - Hx) + abs(Fy - (Hy - 1)); 
    distance[2] = abs(Fx - (Hx + 1)) + abs(Fy - Hy); 
    distance[3] = abs(Fx - Hx) + abs(Fy - (Hy + 1));
    if (map[Hx - 1][Hy] == '*' || map[Hx - 1][Hy] == 'X') 
        distance[0] = 9999;
    if (map[Hx][Hy - 1] == '*' || map[Hx][Hy - 1] == 'X') 
        distance[1] = 9999;
    if (map[Hx + 1][Hy] == '*' || map[Hx + 1][Hy] == 'X') 
        distance[2] = 9999; 
    if (map[Hx][Hy + 1] == '*' || map[Hx][Hy + 1] == 'X') 
        distance[3] = 9999;
    for (i = 0; i < 4; i++) {
        if (min > distance[i]) {
            temp = i;
            min = distance[i];
        }
        else continue;
    }
    return moveble[temp];
}
```

