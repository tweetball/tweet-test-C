#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
//	printf("��һ�仰\n");
//	printf("��һֱ�����˵��Զ���˼侪���磬һ���˼�ʢ����");
	float x, y, a;
	for (y = 1.5; y > -1.5; y -= 0.1) {
		for (x = -1.5; x < 1.5; x += 0.05) {
			a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y <= 0.0 ? 65 : ' ');
		}
		system("color 0c");
		putchar('\n');
	}
//	printf("��һ�仰\n");
//	printf("��һֱ�����˵��Զ���˼侪���磬һ���˼�ʢ����\n");
//	printf("ף����\n");
//	printf("ƽ��ϲ�֣�\n");
	return 0;
}
