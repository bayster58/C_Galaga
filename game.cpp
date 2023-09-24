#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

#define PLAYER_SPEED 3
#define ATTACK_SPEED 30
#define ACK_SPEED 3
#define LEVEL 10
struct{
	int x1;
	int x2;
	int y;
	int ch;
	int hp;
}ENEMYS[15][4] = { 0, };
struct ra{
	int score;
	char name[10];
}rank[11];
int gun[23][19] = { 0, };
int Check_x[60] = { 0, };
int MAX_ENEMY = 3;
int mv_bu = 1;
int mv_cnt = 0;
int speed = 27;
int life = 3;
int score = 0;
int bomb_cnt = 1;
int level = 0;
int revive = 0;
int limit = 11;
int enemy_cnt = 0;
char name[11];
FILE *input, *output;

void gotoxy(int x, int y){
	COORD pos = { 2 * x + 28, y + 3 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void background(){
	int i;
	for (i = 0; i <= 20; i++){
		gotoxy(i + 1, 0);
		putchar('-');
		gotoxy(i + 1, 24);
		putchar('-');
	}
	for (i = 0; i <= 22; i++){
		gotoxy(1, i + 1);
		putchar('|');
		gotoxy(21, i + 1);
		putchar('|');
	}
}
void last(){
	MAX_ENEMY = 3;
	mv_bu = 1;
	mv_cnt = 0;
	speed = 27;
	life = 3;
	score = 0;
	level = 0;
	revive = 0;
	limit = 11;
	enemy_cnt = 0;
	bomb_cnt = 1;
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 15; j++){
			ENEMYS[j][i].x1 = 0;
			ENEMYS[j][i].x2 = 0;
			ENEMYS[j][i].y = 0;
			ENEMYS[j][i].ch = 0;
			ENEMYS[j][i].hp = 0;
		}
	}
	for (i = 0; i < 19; i++){
		for (j = 0; j < 22; j++){
			gun[j][i] = 0;
		}
	}
	for (i = 0; i < 60; i++){
		Check_x[i] = 0;
	}
}
void ENEMY(){

	int i, j, k, tmp = 0;

	for (i = 0; i <= (MAX_ENEMY - 1) / 15; i++){
		if (i == (MAX_ENEMY - 1) / 15){
			for (j = 0; j <= (MAX_ENEMY - 1) % 15;){
				tmp = rand() % 15;
				if (Check_x[tmp + i * 15] == 0){
					Check_x[tmp + i * 15] = 1;
					ENEMYS[j][i].x1 = tmp + 3;
					ENEMYS[j][i].y = i + 2;
					ENEMYS[j][i].hp = 2;
					ENEMYS[j][i].ch = tmp;
					j++;
				}
			}
		}
		else{
			for (j = 0; j < 15;){
				Check_x[i * 15 + j] = 1;
				ENEMYS[j][i].ch = j;
				ENEMYS[14 - j][i].x1 = j + 3;
				ENEMYS[14 - j][i].y = i + 2;
				ENEMYS[14 - j][i].hp = 2;
				j++;
			}
		}
	}
	i--;
	for (k = 0; k <= (MAX_ENEMY - 1) % 15; k++){
		for (j = 0; j <= (MAX_ENEMY - 1) % 15 - 1; j++){
			if (ENEMYS[j][i].x1 < ENEMYS[j + 1][i].x1){
				tmp = ENEMYS[j][i].x1;
				ENEMYS[j][i].x1 = ENEMYS[j + 1][i].x1;
				ENEMYS[j + 1][i].x1 = tmp;
			}
		}
	}
	for (i = 0; i <= (MAX_ENEMY - 1) / 15; i++){
		if (i == (MAX_ENEMY - 1) / 15){
			for (j = 0; j <= (MAX_ENEMY - 1) % 15; j++){
				gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
				printf("ㅜ");
				enemy_cnt++;
			}
		}
		else{
			for (j = 0; j < 15; j++){
				gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
				printf("ㅜ");
				enemy_cnt++;
			}
		}
	}
}
void rm(int i, int j, int l, int k){
	if (ENEMYS[l][k].hp == 2){
		ENEMYS[l][k].hp--;
		gotoxy(j, i);
		printf("※");
		gun[i][j - 2] = 0;
	}
	else if (ENEMYS[l][k].hp == 1){
		score += 10;
		gotoxy(23, 8);
		printf("SCORE : %d", score);
		gotoxy(j, i);
		printf(" ");
		gun[i][j - 2] = 0;
		Check_x[k * 15 + ENEMYS[l][k].ch] = 0;
		ENEMYS[l][k].x1 = 0;
		enemy_cnt--;
	}
}
void MOVE(){
	int i, j, k, l, max = 0, min = 30;

	for (i = 0; i <= (MAX_ENEMY - 1) / 15; i++){
		for (j = 0; j < 15; j++){
			if (ENEMYS[j][i].x1 != 0){
				if (ENEMYS[j][i].x1 > max)
					max = ENEMYS[j][i].x1;
				if (ENEMYS[j][i].x1 < min)
					min = ENEMYS[j][i].x1;
			}
		}
	}
	if ((min == 2 || max == 20) && mv_cnt == 0){
		mv_bu *= -1;
		mv_cnt = 1;
		for (i = (MAX_ENEMY - 1) / 15; i >= 0; i--){
			for (j = 0; j < 15; j++){
				if (ENEMYS[j][i].x1 != 0){
					gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
					printf(" ");
					ENEMYS[j][i].y++;
					gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
					printf("ㅜ");
				}
			}
		}
	}
	else if (mv_bu == 1){
		mv_cnt = 0;
		for (i = 0; i <= (MAX_ENEMY - 1) / 15; i++){
			for (j = 0; j < 15; j++){
				if (ENEMYS[j][i].x1 != 0){
					ENEMYS[j][i].x2 = ENEMYS[j][i].x1;
					ENEMYS[j][i].x1++;
					gotoxy(ENEMYS[j][i].x2, ENEMYS[j][i].y);
					printf(" ");
					gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
					printf("ㅜ");
				}
			}
		}
	}
	else if (mv_bu == -1){
		mv_cnt = 0;
		for (i = (MAX_ENEMY - 1) / 15; i >= 0; i--){
			for (j = 14; j >= 0; j--){
				if (ENEMYS[j][i].x1 != 0){
					ENEMYS[j][i].x2 = ENEMYS[j][i].x1;
					ENEMYS[j][i].x1--;
					gotoxy(ENEMYS[j][i].x2, ENEMYS[j][i].y);
					printf(" ");
					gotoxy(ENEMYS[j][i].x1, ENEMYS[j][i].y);
					printf("ㅜ");
				}
			}
		}
	}
	for (i = 0; i < 22; i++){
		for (j = 0; j < 19; j++){
			if (gun[i][j] == 1){
				for (k = (MAX_ENEMY - 1) / 15; k >= 0; k--){
					for (l = 14; l >= 0; l--){
						if (ENEMYS[l][k].x1 != 0 && j + 2 == ENEMYS[l][k].x1 && i == ENEMYS[l][k].y){
							rm(i, j + 2, l, k);
						}
					}
				}
			}
		}
	}
}
BOOL IsKeyDown(int Key){
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}
void attack(){
	int k, l;
	gun[22][limit - 2] = 1;
	gotoxy(limit, 22);
	printf("＊");
	for (k = (MAX_ENEMY - 1) / 15; k >= 0; k--){
		for (l = 14; l >= 0; l--){
			if (ENEMYS[l][k].x1 != 0 && limit == ENEMYS[l][k].x1 && ENEMYS[l][k].y == 22){
				rm(22, limit, l, k);
			}
		}
	}
}
void ack(){//날라가는 속도
	int i, j, k, l;
	for (i = 0; i < 23; i++){
		for (j = 0; j < 19; j++){
			if (gun[i][j] == 1 && i == 1){
				gotoxy(j + 2, i);
				printf(" ");
			}
			else if (gun[i][j] == 1){
				gun[i - 1][j] = 1;
				gun[i][j] = 0;
				gotoxy(j + 2, i);
				printf(" ");
				gotoxy(j + 2, i + 1);
				printf(" ");
				gotoxy(j + 2, i - 1);
				printf("*");
				for (k = (MAX_ENEMY - 1) / 15; k >= 0; k--){
					for (l = 14; l >= 0; l--){
						if (ENEMYS[l][k].x1 != 0 && j + 2 == ENEMYS[l][k].x1 && i - 1 == ENEMYS[l][k].y){
							rm(i - 1, j + 2, l, k);
						}
					}
				}
			}
		}
	}
}
void bomb(){
	int i, j;
	for (i = (MAX_ENEMY - 1) / 15; i >= 0; i--){
		for (j = 14; j >= 0; j--){
			if (Check_x[i * 15 + ENEMYS[j][i].ch] == 1){
				Check_x[i * 15 + ENEMYS[j][i].ch] = 0;
				score += 10;
			}
		}
	}
	for (i = 0; i < 22; i++){
		for (j = 0; j < 19; j++){
			gun[i][j] = 0;
		}
	}
	gotoxy(23, 8);
	printf("SCORE : %d", score);
	mv_bu = 1;
	mv_cnt = 0;
	enemy_cnt = 0;
	speed -= 1;
	for (i = 1; i <= 23; i++){
		for (j = 2; j <= 20; j++){
			gotoxy(j, i);
			putchar(' ');
		}
	}
}
void reset(){
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 15; j++){
			ENEMYS[j][i] = { 0, };
			Check_x[i * 15 + j] = 0;
		}
	}
	level = 0;
	life -= 1;
	gotoxy(23, 10);
	printf("LIFE : ");
	for (i = 0; i < 3; i++){
		if (i < life){
			printf("♥");
		}
		else
			printf(" ");
	}
	 bomb_cnt = 1;
	 gotoxy(23, 12);
	 printf("BOMB : ");
	 for (i = 0; i < 3; i++){
		 if (i < bomb_cnt){
			 printf("★");
		 }
		 else
			 printf(" ");
	 }
	MAX_ENEMY = 3;
	mv_bu = 1;
	mv_cnt = 0;
	enemy_cnt = 0;
	speed = 20;
	for (i = 20; i <= 23; i++){
		for (j = 2; j <= 20; j++){
			gotoxy(j, i);
			putchar(' ');
		}
	}
}
void play(){
	int i = 0, j;
	int count = 0;
	int cnt = 0;

	srand((unsigned)time(NULL));
	background();

	gotoxy(-10, 4);
	printf("게임 방법");
	gotoxy(-13, 5);
	printf("1. 좌우 화살표로 이동 할");
	gotoxy(-13, 6);
	printf("  수 있습니다.");

	gotoxy(-13, 8);
	printf("2. 공격은 자동공격 입니다.");
	gotoxy(-13, 10);
	printf("3. 폭탄은 스페이스 바를");
	gotoxy(-13, 11);
	printf("  이용해 사용할 수 있습니다.");
	gotoxy(-13, 12);
	printf("  (특정 단계를 깨면 추가)");
	gotoxy(-13, 14);
	printf("4. 적의 체력은 2입니다.");
	gotoxy(-13, 16);
	printf("5. 레벨에 따라 적 비행체의");
	gotoxy(-13, 17);
	printf("  수와 속도가 증가합니다.");
	gotoxy(23, 4);
	printf("NAME : %s", name);
	gotoxy(23, 6);
	printf("LEVEL : %d", level);
	gotoxy(23, 8);
	printf("SCORE : %d", score);
	gotoxy(23, 10);
	printf("LIFE : ");
	for (i = 0; i < life; i++)
		printf("♥");
	gotoxy(23, 12);
	printf("BOMB : ");
	for (i = 0; i < bomb_cnt; i++)
		printf("★");

	while (1){
	re:
		if (enemy_cnt == 0){
			if (MAX_ENEMY != 60){
				MAX_ENEMY += 2;
				speed -= 1;
			}
			level++;
			gotoxy(23, 6);
			printf("LEVEL : %d", level);
			ENEMY();
			if (MAX_ENEMY % 15 == 2 && bomb_cnt < 3){
				bomb_cnt++;
				gotoxy(23, 12);
				printf("BOMB : ");
				for (i = 0; i < 3; i++){
					if (i < bomb_cnt){
						printf("★");
					}
					else
						printf(" ");
				}
			}
		}
		if (count % speed == 1){
			MOVE();
			for (i = (MAX_ENEMY - 1) / 15; i >= 0; i--){
				for (j = 0; j < 15; j++){
					if (ENEMYS[j][i].y >= 23){
						revive++;
						switch (revive){
						case 0: break;
						case 1:
						case 2: reset();
							goto re;
							break;
						case 3:
							Sleep(500);
							return;
							break;
						}
					}
				}
			}
		}
		if (IsKeyDown(VK_SPACE) && bomb_cnt != 0){
			bomb_cnt--;
			bomb();
			gotoxy(23, 12);
			printf("BOMB : ");
			for (i = 0; i < 3; i++){
				if (i < bomb_cnt){
					printf("★");
				}
				else
					printf(" ");
			}
		}
		if (count%5 == 1){
			if (IsKeyDown(VK_LEFT)){
				if (limit >= 3){
					gotoxy(limit, 23);
					putchar(' ');
					limit--;
				}
			}
			else if (IsKeyDown(VK_RIGHT)){
				if (limit <= 19){
					gotoxy(limit, 23);
					putchar(' ');
					limit++;
				}

			}
		}
		if (count%ATTACK_SPEED == 1){
			attack();
		}
		if (count%ACK_SPEED == 1){
			ack();
		}
		Sleep(1);
		gotoxy(limit, 23);
		printf("ㅗ");
		count++;
	}
}
void rank_w(){
	int i, j;
	char a[1000];
	ra tmp;
	output = fopen("sort.txt", "r");
	for (i = 0; i < 10; i++){
		fscanf(output, "%s %d", rank[i].name, &rank[i].score);
	}
	strcpy(rank[10].name, name);
	rank[10].score = score;
	for (i = 0; i < 11; i++){
		for (j = 0; j < 10; j++){
			if (rank[j].score < rank[j + 1].score){
				tmp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = tmp;
			}
		}
	}
	input = fopen("sort.txt", "w+");
	for (i = 0; i < 11; i++){
		fprintf(input, "%s %d\n", rank[i].name, rank[i].score);
	}
	fclose(input);
}
void rank_r(){
	int i, j;
	char a[1000];
	ra tmp;
	output = fopen("sort.txt", "r");
	for (i = 0; i < 10; i++){
		fscanf(output, "%s %d", rank[i].name, &rank[i].score);
	}
	gotoxy(2, 3);
	printf("순위");
	gotoxy(6, 3);
	printf("이름");
	gotoxy(17, 3);
	printf("점수");
	for (i = 0; i < 10; i++){
		gotoxy(2, 5 + i * 2);
		printf("%d", i + 1);
		gotoxy(6, 5 + i * 2);
		printf("%s", rank[i].name);
		gotoxy(17, 5 + i * 2);
		printf("%d", rank[i].score);
	}
}

int main(){
	system("mode con:cols=100 lines=31");
	system("title 비행 슈팅 게임");
	int type;
	int rank_ch;
restart:
	system("cls");
	gotoxy(4, 6);
	printf("1. 게임 시작");
	gotoxy(8, 11);
	printf("2. 랭크 보기");
	gotoxy(12, 16);
	printf("3. 게임 종료");
	gotoxy(-13, 27);
	printf("\nCreated by. Bayster");

	while (1){
		type = getch();
		if (type == 49){
			system("cls");
			gotoxy(-13, 27);
			printf("\nCreated by. Bayster");
			gotoxy(6, 10);
			printf(" 이름을 입력해주세요");
			gotoxy(5, 11);
			printf("(최대 영어 10자 한글 5자)");
			gotoxy(8, 13);
			printf(" ");
			scanf("%10s", name);
			system("cls");
			last();
			play();
			gotoxy(5, 10);
			printf("랭크를 등록하시겠습니까?(Y / N)");
			gotoxy(10, 11);
			printf("SCORE : %d", score);
			gotoxy(12, 12);
			while (1){
				fflush(stdin);
				rank_ch = getch();
				if (rank_ch == 89 || rank_ch == 121){
					system("cls");
					rank_w();
					rank_r();
					Sleep(5000);
					goto restart;
				}
				else if (rank_ch == 78 || rank_ch == 110){
					system("cls");
					goto restart;
				}
			}
		}
		else if (type == 50){
			system("cls");
			gotoxy(-13, 27);
			printf("\nCreated by. Bayster");
			rank_r();
			Sleep(8000);
			goto restart;
		}
		else if (type == 51){
			system("cls");
			gotoxy(-13, 27);
			printf("\nCreated by. Bayster");
			gotoxy(8, 11);
			printf("Bye Bye~~~~");
			Sleep(1200);
			return 0;
		}
	}
}