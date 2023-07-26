#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
HANDLE JB = GetStdHandle(STD_OUTPUT_HANDLE);

void zuobiao(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(JB, pos);
}

void color(int a) {
	if (a <= 16)
		SetConsoleTextAttribute(JB, a);
	else
		SetConsoleTextAttribute(JB, 7);
}

void yanshi() {
	for (int m = 0; m < 50000000; m++);
	for (int m = 0; m < 50000000; m++);
	for (int m = 0; m < 50000000; m++);
}

void lihe1() {
	int i;
	for (i = 0; i < 2; i++) {
		printf("\t");
	}
	color(14);
	putchar(16);
	putchar(17);
	for (i = 0; i < 3; i++) {
		printf("\t");
	}
	color(6);
	putchar(16);
	putchar(17);
	printf("\n");
	for (i = 0; i < 2; i++) {
		printf("\t");
	}
	SetConsoleTextAttribute(JB, 207);
	putchar(223);
	SetConsoleTextAttribute(JB, 207);
	putchar(220);
	for (i = 0; i < 3; i++) {
		printf("\t");
	}
	SetConsoleTextAttribute(JB, 71);
	putchar(223);
	SetConsoleTextAttribute(JB, 71);
	putchar(220);
	printf("\n");
	color(7);
}

void lihe2() {
	int i;
	for (i = 0; i < 2; i++) {
		printf("\t");
	}
	color(6);
	putchar(16);
	putchar(17);
	for (i = 0; i < 3; i++) {
		printf("\t");
	}
	color(14);
	putchar(16);
	putchar(17);
	color(7);
	printf("\n");
	for (i = 0; i < 2; i++) {
		printf("\t");
	}
	SetConsoleTextAttribute(JB, 71);
	putchar(223);
	SetConsoleTextAttribute(JB, 71);
	putchar(220);
	for (i = 0; i < 3; i++) {
		printf("\t");
	}
	SetConsoleTextAttribute(JB, 207);
	putchar(223);
	SetConsoleTextAttribute(JB, 207);
	putchar(220);
	printf("\n");
	color(7);
}

void shu1() {
	color(6);
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf("  *\n");
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf("*****\n");
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf(" * *\n");
	//
	color(2);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			printf("\t   ");
		}
		for (int j = 0; j < (6 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			printf("     ");
		}
		for (int j = 0; j < (15 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 3; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			printf("   ");
		}
		for (int j = 0; j < (19 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++);
		{
			printf("\t\t      ");
		}
		for (int j = 0; j < 9; j++) {
			if (j % 2 == 0) {
				SetConsoleTextAttribute(JB, 262);
				printf("%c", 222);
				color(7);
			}

			else {
				SetConsoleTextAttribute(JB, 262);
				printf("$");
				color(7);
			}

		}
		printf("\n");
	}
}

void shu2() {
	color(14);
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf("  *\n");
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf("*****\n");
	for (int i = 0; i < 3; i++) {
		printf("\t");
	}
	printf(" * *\n");
	//
	color(10);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			printf("\t   ");
		}
		for (int j = 0; j < (6 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			printf("     ");
		}
		for (int j = 0; j < (15 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 3; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			printf("   ");
		}
		for (int j = 0; j < (19 - 2 * i); j++) {
			printf(" ");
		}
		for (int j = 0; j < (4 * i + 3); j++) {
			printf("%c", '^');
		}
		printf("\n");
	}
	//
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++);
		{
			printf("\t\t      ");
		}
		for (int j = 0; j < 9; j++) {
			if (j % 2 == 0) {
				SetConsoleTextAttribute(JB, 262);
				printf("%c", 222);
				color(7);
			}

			else {
				SetConsoleTextAttribute(JB, 110);
				printf("$");
				color(7);
			}

		}
		printf("\n");
	}
}

void qita() {
	zuobiao(23, 6);
	color(12);
	printf("\b%c", 1);
	zuobiao(33, 9);
	printf("\b%c", 2);
	zuobiao(21, 10);
	printf("\b%c", 3);
	zuobiao(24, 13);
	printf("\b%c", 1);
	color(11);
	zuobiao(30, 5);
	printf("\b%c", 3);
	zuobiao(28, 11);
	printf("\b%c", 1);
	zuobiao(34, 14);
	printf("\b%c", 2);
	color(13);
	zuobiao(18, 14);
	printf("\b%c", 1);
	zuobiao(26, 8);
	printf("\b%c", 3);
	color(7);
}

void xuehua1() {
	zuobiao(5, 7);
	printf("*");
	zuobiao(8, 6);
	printf("*");
	zuobiao(4, 3);
	printf("*");
	zuobiao(7, 10);
	printf("*");
	zuobiao(34, 16);
	printf("*");
	zuobiao(45, 25);
	printf("*");
	zuobiao(35, 7);
	printf("*");
	zuobiao(45, 3);
	printf("*");
	zuobiao(38, 5);
	printf("*");
	zuobiao(17, 7);
	printf("*");
	zuobiao(3, 7);
	printf("*");
	zuobiao(53, 7);
	printf("*");
	zuobiao(55, 5);
	printf("*");
	zuobiao(45, 6);
	printf("*");
	zuobiao(35, 4);
	printf("*");
	zuobiao(53, 10);
	printf("*");
	zuobiao(13, 10);
	printf("*");
	zuobiao(4, 13);
	printf("*");
	zuobiao(51, 9);
	printf("*");
	zuobiao(8, 7);
	printf("*");
	zuobiao(45, 3);
	printf("*");
	zuobiao(5, 20);
	printf("*");
	zuobiao(3, 18);
	printf("*");
	zuobiao(7, 21);
	printf("*");
	zuobiao(36, 18);
	printf("*");
	zuobiao(38, 17);
	printf("*");
	zuobiao(40, 20);
	printf("*");
	zuobiao(13, 17);
	printf("*");
	zuobiao(45, 11);
	printf("*");
	zuobiao(42, 12);
	printf("*");
	zuobiao(46, 15);
	printf("*");
	zuobiao(48, 17);
	printf("*");
	zuobiao(49, 20);
	printf("*");
	zuobiao(51, 22);
	printf("*");
}

void xuehua2() {
	zuobiao(5, 9);
	printf("*");
	zuobiao(8, 8);
	printf("*");
	zuobiao(4, 5);
	printf("*");
	zuobiao(7, 12);
	printf("*");
	zuobiao(34, 18);
	printf("*");
	zuobiao(45, 27);
	printf("*");
	zuobiao(37, 11);
	printf("*");
	zuobiao(45, 5);
	printf("*");
	zuobiao(38, 7);
	printf("*");
	zuobiao(17, 8);
	printf("*");
	zuobiao(3, 9);
	printf("*");
	zuobiao(53, 8);
	printf("*");
	zuobiao(55, 7);
	printf("*");
	zuobiao(45, 8);
	printf("*");
	zuobiao(35, 6);
	printf("*");
	zuobiao(53, 12);
	printf("*");
	zuobiao(13, 12);
	printf("*");
	zuobiao(4, 15);
	printf("*");
	zuobiao(51, 11);
	printf("*");
	zuobiao(8, 9);
	printf("*");
	zuobiao(45, 5);
	printf("*");
	zuobiao(5, 22);
	printf("*");
	zuobiao(3, 20);
	printf("*");
	zuobiao(7, 23);
	printf("*");
	zuobiao(36, 20);
	printf("*");
	zuobiao(38, 19);
	printf("*");
	zuobiao(40, 3);
	printf("*");
	zuobiao(13, 19);
	printf("*");
	zuobiao(45, 13);
	printf("*");
	zuobiao(42, 14);
	printf("*");
	zuobiao(46, 17);
	printf("*");
	zuobiao(48, 4);
	printf("*");
	zuobiao(49, 2);
	printf("*");
	zuobiao(51, 24);
	printf("*");
}

int main() {
	int x, y, a, b, c, i, j;
	SetConsoleOutputCP(437);
	while (1) {
		shu1();
		lihe1();
		qita();
		xuehua1();
		yanshi();
		yanshi();
		yanshi();
		system("cls");
		shu2();
		lihe2();
		qita();
		xuehua2();
		yanshi();
		yanshi();
		system("cls");
		//
		zuobiao(100, 100);
		int ran = rand();
		printf("%d", ran);
	}

	return 0;
}