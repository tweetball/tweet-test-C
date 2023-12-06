#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
//	printf("有一句话\n");
//	printf("我一直想对你说：远赴人间惊鸿宴，一睹人间盛世颜");
	float x, y, a;
	for (y = 1.5; y > -1.5; y -= 0.1) {
		for (x = -1.5; x < 1.5; x += 0.05) {
			a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y <= 0.0 ? 65 : ' ');
		}
		system("color 0c");
		putchar('\n');
	}
//	printf("有一句话\n");
//	printf("我一直想对你说：远赴人间惊鸿宴，一睹人间盛世颜\n");
//	printf("祝我们\n");
//	printf("平安喜乐！\n");
	return 0;
}
