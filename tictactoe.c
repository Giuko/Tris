#include <stdio.h>
#include <conio.h>

#define getch() _getch()

#ifdef __unix__
#define CLRSCR() system("clear")
#elif _WIN32
#define CLRSCR() system("cls")

#endif // _WIN32

#define ARROW 224 
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

#define EXIT_CODE 300
#define RETURN 13

int chechArrow(int pos) {
	int move = getch();
	switch (move)
	{
	case 77:
		if ((pos + 1) % 3 != 0)
			return 1;
		break;
	case 75:
		if (pos % 3 != 0) 
			return -1;
		break;
	case 80:
		if (pos < 6)
			return 3;
		break;
	case 72:
		if (pos > 2)
			return -3;
		break;
	}
	return 0;
}

int drawBox(int pos, char *play, int player) {
	
	int i;
	printf("Player %d", player);
	for (i = 0; i < 9; ++i) {
		if (i % 3 == 0)
			printf("\n-------------------------\n|");
		if (i == pos)
			printf(" [ %c ] |", play[i]);
		else
			printf("   %c   |", play[i]);
	}
}

int checkRow(char play[]) {
	int i;
	for (i = 0; i < 3; ++i) {
		if ((play[i * 3] == play[i * 3 + 1] && play[i * 3] == play[i * 3 + 2]) && play[i*3] != ' ') {
			return 1;
		}
	}
	return 0;
}
int checkCol(char play[]) {
	int i;
	for (i = 0; i < 3; ++i) {
		if (play[i] == play[i + 3 * 1] && play[i] == play[i + 3 * 2] && play[i] != ' ') {
			return 1;
		}
	}
	return 0;
}

int checkDiagonal(char play[]) {
	if (play[0] == play[4] && play[0] == play[8] && play[0] != ' ') {
		return 1;
	}else if (play[2] == play[4] && play[2] == play[6] && play[2] != ' ') {
		return 1;
	}
	return 0;
}

int fullGrid(char grid[]) {
	int i;
	for (i = 0; i < 9; ++i) {
		if (grid[i] == ' ')
			return 0;
	}
	return 1;
}

int checkWin(char play[], int player, int *pos) {
	if (checkRow(play) || checkCol(play) || checkDiagonal(play)) {
		*pos = 300;
		CLRSCR();
		printf("Player %d: WIN\n", player);
		getch();
		return 0;
	}
	if (fullGrid(play)) {
		*pos = 300;
		CLRSCR();
		printf("DRAW\n", player);
		getch();
		return 0;
	}
}

int main(void) {
	int pos = 0, player = 1;
	int firstGetch;
	char play[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	do {
		CLRSCR();
		drawBox(pos, play, player);
		firstGetch = getch();
		if (firstGetch == ARROW)
			pos += chechArrow(pos);
		else if(firstGetch == RETURN) {
			if (player == 1) {
				if (play[pos] == ' ') {
					play[pos] = 'X'; 
					checkWin(play, player, &pos);
					player = 2;
				}
			}
			else {
				if (play[pos] == ' ') {
					play[pos] = 'O';
					checkWin(play, player, &pos);
					player = 1;
				}
			}
		}
	} while (pos != EXIT_CODE);
}
