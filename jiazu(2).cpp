#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 常量定义
#define MAX_MEMBERS 100

// 家庭成员结构体
typedef struct {
	char *name;             // 成员姓名
	char *birthdate;        // 出生日期
	char *maritalStatus;    // 婚姻状况
	char *address;          // 地址
	int alive;              // 是否健在
	char *deathDate;        // 死亡日期
	char **children;        // 孩子姓名数组
	int numChildren;        // 孩子数量
	int generation;         // 成员所属的代数
} FamilyMember;

// 家谱结构体
typedef struct {
	FamilyMember *members[MAX_MEMBERS]; // 所有成员
	int numMembers;                      // 成员数量
} FamilyTree;

// 队列结构体
typedef struct {
	FamilyMember *data[MAX_MEMBERS];
	int front;
	int rear;
} Queue;

// 函数声明：
//初始化家族成员
FamilyMember *createMember(const char *name, const char *birthdate, const char *maritalStatus, const char *address,
                           int alive, const char *deathDate);
//添加成员
void addMember(FamilyTree *familyTree, FamilyMember *member);
//显示家族第几代
void displayGeneration(const FamilyTree *familyTree, int generation);
//按照名字寻找信息
FamilyMember *searchByName(const FamilyTree *familyTree, const char *name);
//按照生日寻找名字
void searchByBirthdate(const FamilyTree *familyTree, const char *birthdate);
//添加孩子
void addChild(FamilyTree *familyTree, const char *parentName, FamilyMember *child);
//释放家族成员动态内存空间
void freeMember(FamilyMember *member);
//释放家谱动态内存空间
void freeFamilyTree(FamilyTree *familyTree);

// 辅助函数，根据姓名查找成员的上一代（父亲）
FamilyMember *findParent(const FamilyTree *familyTree, const FamilyMember *member) ;
// 初始化队列
void initQueue(Queue *queue) ;
// 队列是否为空
int isEmpty(const Queue *queue) ;
// 队列是否已满
int isFull(const Queue *queue) ;
// 入队
void enqueue(Queue *queue, FamilyMember *member);
// 出队
FamilyMember *dequeue(Queue *queue);
// 辅助函数，根据姓名查找成员在家谱中的索引
int findIndexByName(const FamilyTree *familyTree, const char *name) ;
// 递归删除成员及其后代
void removeMemberRecursively(FamilyTree *familyTree, FamilyMember *member) ;
// 移除成员及其后代
void removeMember(FamilyTree *familyTree, const char *name) ;
// 修改孩子信息
void addChild2(FamilyTree *familyTree, const char *parentName, FamilyMember *child) ;

int main() {
	FamilyTree familyTree;
	familyTree.numMembers = 0;
	// 添加至少30个成员的数据
	// 1 代
	FamilyMember *member1 = createMember("爷爷", "1900-01-01", "未婚", "北京", 0, "1980-01-01");
	member1->generation = 1;
	addMember(&familyTree, member1);

	// 2 代
	FamilyMember *member2 = createMember("爸爸", "1930-01-01", "已婚", "北京", 0, "1990-01-01");
	member2->generation = 2;
	addChild(&familyTree, "爷爷", member2);

	FamilyMember *member3 = createMember("老姑", "1935-01-01", "已婚", "上海", 1, "");
	member3->generation = 2;
	addChild(&familyTree, "爷爷", member3);

	FamilyMember *member4 = createMember("叔叔", "1955-01-01", "未婚", "北京", 1, "");
	member4->generation = 2;
	addChild(&familyTree, "爷爷", member4);

	FamilyMember *member5 = createMember("阿姨", "1960-01-01", "已婚", "上海", 1, "");
	member5->generation = 2;
	addChild(&familyTree, "爷爷", member5);

	FamilyMember *member6 = createMember("爸爸的兄弟", "1950-01-01", "已婚", "北京", 1, "");
	member6->generation = 2;
	addChild(&familyTree, "爷爷", member6);

	FamilyMember *member7 = createMember("爸爸的姐妹", "1952-01-01", "已婚", "北京", 1, "");
	member7->generation = 2;
	addChild(&familyTree, "爷爷", member7);

	// 3 代
	FamilyMember *member8 = createMember("叔叔的儿子1", "1980-01-01", "未婚", "北京", 1, "");
	member8->generation = 3;
	addChild(&familyTree, "叔叔", member8);

	FamilyMember *member9 = createMember("叔叔的儿子2", "1982-01-01", "未婚", "北京", 1, "");
	member9->generation = 3;
	addChild(&familyTree, "叔叔", member9);

	FamilyMember *member10 = createMember("阿姨的女儿1", "1985-01-01", "未婚", "上海", 1, "");
	member10->generation = 3;
	addChild(&familyTree, "阿姨", member10);

	FamilyMember *member11 = createMember("阿姨的女儿2", "1988-01-01", "未婚", "上海", 1, "");
	member11->generation = 3;
	addChild(&familyTree, "阿姨", member11);

	// 4 代
	FamilyMember *member12 = createMember("叔叔的孙子1", "2005-01-01", "未婚", "北京", 1, "");
	member12->generation = 4;
	addChild(&familyTree, "叔叔的儿子1", member12);

	FamilyMember *member13 = createMember("叔叔的孙子2", "2008-01-01", "未婚", "北京", 1, "");
	member13->generation = 4;
	addChild(&familyTree, "叔叔的儿子1", member13);

	FamilyMember *member14 = createMember("阿姨的外孙女1", "2010-01-01", "未婚", "上海", 1, "");
	member14->generation = 4;
	addChild(&familyTree, "阿姨的女儿1", member14);

	FamilyMember *member15 = createMember("阿姨的外孙女2", "2012-01-01", "未婚", "上海", 1, "");
	member15->generation = 4;
	addChild(&familyTree, "阿姨的女儿2", member15);
	int choice;
	while (1) {
		printf("\n家谱管理系统：\n");
		printf("1. 显示某一代成员\n");
		printf("2. 按姓名查询\n");
		printf("3. 按出生日期查询\n");
		printf("4. 添加孩子\n");
		printf("5. 移除成员\n");
		printf("6. 修改成员信息\n");
		printf("7. 退出\n");

		printf("请输入您的选择（1-7）：");
		if (scanf("%d", &choice) != 1) {
			scanf("%*[^\n]");
			printf("输入错误，请输入一个数字。\n");
			continue;
		}

		switch (choice) {
			// 情况1：用户输入一个代数，显示该代的家谱信息
			case 1: {
				// 声明一个整型变量用于存储用户输入的代数
				int generation;
				// 提示用户输入代数
				printf("请输入代数：");
				// 使用scanf函数尝试读取用户输入的代数，如果返回值不为1，说明输入不是一个有效的数字
				if (scanf("%d", &generation) != 1) {
					// 打印错误信息，并提示用户输入一个数字
					printf("输入错误，请输入一个数字。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}
				// 调用displayGeneration函数，显示指定代数的家谱信息
				displayGeneration(&familyTree, generation);
				// 跳出当前情况的处理，继续执行下一个情况
				break;
			}
			// 情况2：按姓名查询家谱成员信息
			case 2: {
				// 声明一个字符数组用于存储用户输入的姓名
				char name[50];
				// 提示用户输入要查询的姓名
				printf("请输入要查询的姓名：");
				// 使用scanf函数尝试读取用户输入的姓名，如果返回值不为1，说明输入不合法
				if (scanf("%s", name) != 1) {
					// 打印错误信息，并提示用户输入正确的姓名
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}
				// 调用searchByName函数，根据姓名在家谱中查找成员
				FamilyMember *member = searchByName(&familyTree, name);
				// 如果找到成员
				if (member) {
					// 显示成员的基本信息
					printf("\n%s 的详细信息：\n", name);
					printf("姓名：%s\n", member->name);
					printf("出生日期：%s\n", member->birthdate);
					printf("婚姻状况：%s\n", member->maritalStatus);
					printf("地址：%s\n", member->address);
					printf("是否健在：%s\n", member->alive ? "是" : "否");
					// 如果成员已故，显示死亡日期
					if (!member->alive) {
						printf("死亡日期：%s\n", member->deathDate);
					}

					// 显示父亲信息
					FamilyMember *father = findParent(&familyTree, member);
					// 如果找到父亲
					if (father) {
						printf("\n%s 的父亲信息：\n", name);
						printf("姓名：%s\n", father->name);
						printf("出生日期：%s\n", father->birthdate);
						printf("婚姻状况：%s\n", father->maritalStatus);
						printf("地址：%s\n", father->address);
						printf("是否健在：%s\n", father->alive ? "是" : "否");
						// 如果父亲已故，显示死亡日期
						if (!father->alive) {
							printf("死亡日期：%s\n", father->deathDate);
						}
						// 显示父亲所在代数
						printf("第 %d 代\n", father->generation);
					} else {
						// 如果未找到父亲，输出提示信息
						printf("\n%s 未找到父亲。\n", name);
					}
					printf("\n");

					// 显示孩子信息
					if (member->numChildren > 0) {
						printf("孩子们：\n");
						// 遍历成员的孩子列表
						for (int i = 0; i < member->numChildren; i++) {
							// 根据孩子姓名在家谱中查找孩子信息
							FamilyMember *child = searchByName(&familyTree, member->children[i]);
							// 如果找到孩子
							if (child) {
								// 输出孩子的姓名
								printf("- %s\n", child->name);
								// 输出孩子的详细信息
								printf("  出生日期：%s\n", child->birthdate);
								printf("  婚姻状况：%s\n", child->maritalStatus);
								printf("  地址：%s\n", child->address);
								printf("  是否健在：%s\n", child->alive ? "是" : "否");
								// 如果孩子已故，显示死亡日期
								if (!child->alive) {
									printf("  死亡日期：%s\n", child->deathDate);
								}
								// 显示孩子所在代数
								printf("  第 %d 代\n", child->generation);
							}
						}
					} else {
						// 如果没有孩子，输出提示信息
						printf("暂无孩子。\n");
					}
				} else {
					// 如果未找到成员，输出提示信息
					printf("未找到姓名为 '%s' 的成员。\n", name);
				}
				// 跳出当前情况的处理，继续执行下一个情况
				break;
			}


			case 3: {
				// 用户选择情况3：按出生日期查询家谱成员信息

				// 声明一个字符数组用于存储用户输入的出生日期
				char birthdate[20];
				// 提示用户输入要查询的出生日期
				printf("请输入要查询的出生日期：");
				// 使用scanf函数尝试读取用户输入的出生日期，如果返回值不为1，说明输入不合法
				if (scanf("%s", birthdate) != 1) {
					// 打印错误信息，并提示用户输入正确的出生日期
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}
				// 调用searchByBirthdate函数，根据出生日期在家谱中查找成员
				searchByBirthdate(&familyTree, birthdate);
				// 跳出当前情况的处理，继续执行下一个情况
				break;
			}

			case 4: {
				// 用户选择情况4：添加孩子到家谱

				// 声明字符数组，用于存储用户输入的父母姓名、孩子姓名、孩子出生日期、孩子出生地址、是否结婚
				char parentName[50];
				char childName[50];
				char childBirthdate[20];
				char childBirthloc[50];
				char marryornot[4];

				// 提示用户输入父母的姓名
				printf("请输入父母的姓名：");
				// 使用scanf函数尝试读取用户输入的父母姓名，如果返回值不为1，说明输入不合法
				if (scanf("%s", parentName) != 1) {
					// 打印错误信息，并提示用户输入正确的父母姓名
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 根据父母姓名在家谱中查找父母信息
				FamilyMember *parent = searchByName((const FamilyTree *)&familyTree, parentName);

				// 计算孩子所在代数
				int childGeneration = parent->generation + 1;

				// 提示用户输入孩子的姓名
				printf("请输入孩子的姓名：");
				// 使用scanf函数尝试读取用户输入的孩子姓名，如果返回值不为1，说明输入不合法
				if (scanf("%s", childName) != 1) {
					// 打印错误信息，并提示用户输入正确的孩子姓名
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 提示用户输入孩子的出生日期
				printf("请输入孩子的出生日期：");
				// 使用scanf函数尝试读取用户输入的孩子出生日期，如果返回值不为1，说明输入不合法
				if (scanf("%s", childBirthdate) != 1) {
					// 打印错误信息，并提示用户输入正确的孩子出生日期
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 提示用户输入孩子的出生地址
				printf("请输入孩子的出生地址：");
				// 使用scanf函数尝试读取用户输入的孩子出生地址，如果返回值不为1，说明输入不合法
				if (scanf("%s", childBirthloc) != 1) {
					// 打印错误信息，并提示用户输入正确的孩子出生地址
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 提示用户输入孩子是否结婚
				printf("是否结婚？ (是/否): ");
				// 使用scanf函数尝试读取用户输入的是否结婚信息，如果返回值不为1，说明输入不合法
				if (scanf("%s", marryornot) != 1) {
					// 打印错误信息，并提示用户输入正确的是否结婚信息
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 调用createMember函数创建孩子成员
				FamilyMember *child = createMember(childName, childBirthdate, marryornot, childBirthloc, 1, "");
				// 调用addChild函数将孩子添加到家谱中
				addChild(&familyTree, parentName, child);
				// 设置孩子所在代数
				child->generation = childGeneration;
				// 跳出当前情况的处理，继续执行下一个情况
				break;

			}

			case 5: {
				// 用户选择情况5：移除家谱中的成员

				// 声明字符数组，用于存储用户输入的成员姓名
				char memberName[50];
				// 提示用户输入要移除的成员姓名
				printf("请输入要移除的成员姓名：");
				// 使用scanf函数尝试读取用户输入的成员姓名，如果返回值不为1，说明输入不合法
				if (scanf("%s", memberName) != 1) {
					// 打印错误信息，并提示用户输入正确的成员姓名
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}
				// 调用removeMember函数，从家谱中移除指定姓名的成员
				removeMember(&familyTree, memberName);
				// 跳出当前情况的处理，继续执行下一个情况
				break;
			}
			case 6: {
				// 用户选择情况6：修改家谱成员信息

				// 声明字符数组，用于存储用户输入的成员姓名、是否健在、是否修改父母关系、是否修改孩子关系
				char memberName[50];
				char deadornot[8];
				char yesorno[8];

				// 提示用户输入要修改信息的成员姓名
				printf("请输入要修改信息的成员姓名：");
				// 使用scanf函数尝试读取用户输入的成员姓名，如果返回值不为1，说明输入不合法
				if (scanf("%s", memberName) != 1) {
					// 打印错误信息，并提示用户输入正确的成员姓名
					printf("输入错误。\n");
					// 跳出当前情况的处理，继续执行下一个情况
					break;
				}

				// 根据成员姓名在家谱中查找成员信息
				FamilyMember *member = searchByName(&familyTree, memberName);
				char originalName[50]; // 临时存储原始名字的数组

				// 保存原始名字
				strcpy(originalName, member->name);
				//寻找父亲
				FamilyMember *oldParent = findParent(&familyTree, member);
				// 如果找到成员
				if (member) {
					// 提示用户输入新的姓名
					printf("请输入新的姓名：");
					// 使用scanf函数尝试读取用户输入的新姓名，如果返回值不为1，说明输入不合法
					if (scanf("%s", member->name) != 1) {
						// 打印错误信息，并提示用户输入正确的新姓名
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 提示用户输入新的出生日期
					printf("请输入新的出生日期：");
					// 使用scanf函数尝试读取用户输入的新出生日期，如果返回值不为1，说明输入不合法
					if (scanf("%s", member->birthdate) != 1) {
						// 打印错误信息，并提示用户输入正确的新出生日期
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 提示用户输入新的婚姻状况
					printf("请输入新的婚姻状况：");
					// 使用scanf函数尝试读取用户输入的新婚姻状况，如果返回值不为1，说明输入不合法
					if (scanf("%s", member->maritalStatus) != 1) {
						// 打印错误信息，并提示用户输入正确的新婚姻状况
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 提示用户输入新的地址
					printf("请输入新的地址：");
					// 使用scanf函数尝试读取用户输入的新地址，如果返回值不为1，说明输入不合法
					if (scanf("%s", member->address) != 1) {
						// 打印错误信息，并提示用户输入正确的新地址
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 提示用户输入成员是否健在
					printf("成员是否健在？（是/否）：");
					// 使用scanf函数尝试读取用户输入的是否健在信息，如果返回值不为1，说明输入不合法
					if (scanf("%s", deadornot) != 1) {
						// 打印错误信息，并提示用户输入正确的是否健在信息
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 根据用户输入更新成员是否健在的状态
					if (strcmp(deadornot, "否") == 0) {
						member->alive = 0;
						// 提示用户输入死亡日期
						printf("请输入死亡日期：");
						// 使用scanf函数尝试读取用户输入的死亡日期，如果返回值不为1，说明输入不合法
						if (scanf("%s", member->deathDate) != 1) {
							// 打印错误信息，并提示用户输入正确的死亡日期
							printf("输入错误。\n");
							// 跳出当前情况的处理，继续执行下一个情况
							break;
						}
					} else {
						member->alive = 1;
					}

					// 提示用户是否需要修改父母关系
					printf("是否需要修改父母的关系？ (是/否): ");
					// 使用scanf函数尝试读取用户输入的是否修改父母关系的信息，如果返回值不为1，说明输入不合法
					if (scanf("%s", yesorno) != 1) {
						// 打印错误信息，并提示用户输入正确的是否修改父母关系的信息
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 如果用户选择是，提示用户输入新的父亲/母亲的姓名
					if (strcmp(yesorno, "是") == 0) {
						char newParentName[50];
						printf("请输入新的父亲/母亲的姓名：");
						// 使用scanf函数尝试读取用户输入的新父亲/母亲姓名，如果返回值不为1，说明输入不合法
						if (scanf("%s", newParentName) != 1) {
							// 打印错误信息，并提示用户输入正确的新父亲/母亲姓名
							printf("输入错误。\n");
							// 跳出当前情况的处理，继续执行下一个情况
							break;
						}
						// 移除当前父母关系
						FamilyMember *oldParent = findParent(&familyTree, member);

						// 如果找到当前父母
						if (oldParent) {
							// 遍历父母的孩子列表
							for (int i = 0; i < oldParent->numChildren; i++) {
								// 找到与成员姓名匹配的孩子
								if (strcmp(oldParent->children[i], member->name) == 0) {
									// 释放孩子的内存空间
									free(oldParent->children[i]);
									// 移动数组元素，删除当前孩子
									for (int j = i; j < oldParent->numChildren - 1; j++) {
										oldParent->children[j] = oldParent->children[j + 1];
									}
									// 减少父母的孩子数量
									oldParent->numChildren--;
									// 找到匹配项后，退出循环
									break;
								}
							}
						}
						// 添加新的父母关系
						FamilyMember *newParent = searchByName(&familyTree, newParentName);

						// 如果找到新的父亲/母亲
						if (newParent) {
							// 调用addChild2函数，将成员添加为新父亲/母亲的孩子
							addChild2(&familyTree, newParentName, member);
							// 打印提示信息，表示父母关系已更新
							printf("%s 的父母关系已更新。\n", member->name);
						} else {
							// 如果未找到新的父亲/母亲，打印提示信息
							printf("未找到名为 '%s' 的父亲/母亲。\n", newParentName);
						}
					}
					// 如果用户选择否，提示用户的之前父母关系。
					else {
						// 用户选择不修改父母关系的情况
						// 如果之前有父母关系，将之前的父母的孩子名字更改为现在的名字

						if (oldParent) {
							for (int i = 0; i < oldParent->numChildren; i++) {
								if (strcmp(oldParent->children[i], originalName) == 0) {
									// 释放之前的孩子名字
									free(oldParent->children[i]);
									// 分配新的孩子名字，并复制成员的名字
									oldParent->children[i] = strdup(member->name);
									if (!oldParent->children[i]) {
										// 内存分配失败的处理逻辑
										printf("内存分配失败。\n");
										exit(EXIT_FAILURE);
									}
									// 找到匹配项后，退出循环
									break;
								}
							}
						}
					}


					// 提示用户是否需要修改孩子关系
					printf("是否需要修改孩子的关系？ (是/否): ");
					// 使用scanf函数尝试读取用户输入的是否修改孩子关系的信息，如果返回值不为1，说明输入不合法
					if (scanf("%s", yesorno) != 1) {
						// 打印错误信息，并提示用户输入正确的是否修改孩子关系的信息
						printf("输入错误。\n");
						// 跳出当前情况的处理，继续执行下一个情况
						break;
					}

					// 如果用户选择是，提示用户输入新的孩子姓名
					if (strcmp(yesorno, "是") == 0) {
						char newChildName[50];
						printf("请输入新的孩子的姓名：");
						// 使用scanf函数尝试读取用户输入的新孩子姓名，如果返回值不为1，说明输入不合法
						if (scanf("%s", newChildName) != 1) {
							// 打印错误信息，并提示用户输入正确的新孩子姓名
							printf("输入错误。\n");
							// 跳出当前情况的处理，继续执行下一个情况
							break;
						}

						// 移除当前孩子关系
						for (int i = 0; i < member->numChildren; i++) {
							// 找到与新孩子姓名匹配的孩子
							if (strcmp(member->children[i], newChildName) == 0) {
								// 释放孩子的内存空间
								free(member->children[i]);
								// 移动数组元素，删除当前孩子
								for (int j = i; j < member->numChildren - 1; j++) {
									member->children[j] = member->children[j + 1];
								}
								// 减少成员的孩子数量
								member->numChildren--;
								// 找到匹配项后，退出循环
								break;
							}
						}

						// 添加新的孩子关系
						FamilyMember *newChild = searchByName(&familyTree, newChildName);

						// 如果找到新的孩子
						if (newChild) {
							// 调用addChild2函数，将新孩子添加为成员的孩子
							addChild2(&familyTree, member->name, newChild);
							// 打印提示信息，表示孩子关系已更新
							printf("%s 的孩子关系已更新。\n", member->name);
						} else {
							// 如果未找到新的孩子，打印提示信息
							printf("未找到名为 '%s' 的孩子。\n", newChildName);
						}
					}
				} else {
					// 如果未找到成员，输出提示信息
					printf("未找到名为 '%s' 的成员。\n", memberName);
				}
				// 跳出当前情况的处理，继续执行下一个情况
				break;

			}
			case 7: {
				printf("退出家谱管理系统。\n");
				exit(0);
				freeFamilyTree(&familyTree); // 释放家谱内存
			}
			default: {
				printf("无效的选择，请输入1到7之间的数字。\n");
				continue;
			}

		}
	}
	return 0;
}

// 创建成员
FamilyMember *createMember(const char *name, const char *birthdate, const char *maritalStatus, const char *address,

                           int alive, const char *deathDate) {
	// 分配内存空间，用于存储FamilyMember结构体
	FamilyMember *member = (FamilyMember *)calloc(1, sizeof(FamilyMember));
	// 检查内存分配是否成功
	if (!member) {
		// 如果分配失败，打印错误信息，并退出程序
		printf("内存分配失败。\n");
		exit(EXIT_FAILURE);
	}

	// 使用strdup函数复制字符串，分配新的内存空间，避免指针共享
	member->name = name ? strdup(name) : NULL;
	member->birthdate = birthdate ? strdup(birthdate) : NULL;
	member->maritalStatus = maritalStatus ? strdup(maritalStatus) : NULL;
	member->address = address ? strdup(address) : NULL;
	member->alive = alive;
	member->deathDate = deathDate ? strdup(deathDate) : NULL;
	member->numChildren = 0;
	member->children = NULL;

	// 返回创建的成员结构体指针
	return member;
}

// 添加孩子
void addChild(FamilyTree *familyTree, const char *parentName, FamilyMember *child) {
	// 打印调试信息
	printf("Adding child %s to parent %s in addChild function\n", child->name, parentName);

	// 检查参数是否为NULL
	if (!familyTree || !parentName || !child) {
		// 打印错误信息，参数错误
		printf("参数错误。\n");
		return;
	}

	// 根据父亲/母亲姓名查找父亲/母亲成员
	FamilyMember *parent = searchByName(familyTree, parentName);

	// 如果父亲/母亲存在
	if (parent) {
		// 增加父亲/母亲的孩子数量
		parent->numChildren++;

		// 重新分配父亲/母亲的孩子列表的内存
		parent->children = (char **)realloc(parent->children, sizeof(char *) * parent->numChildren);
		if (!parent->children) {
			// 打印错误信息，内存分配失败
			printf("内存分配失败。\n");
			exit(EXIT_FAILURE);
		}

		// 将孩子姓名添加到父亲/母亲的孩子列表中
		parent->children[parent->numChildren - 1] = child->name ? strdup(child->name) : NULL;
		if (!parent->children[parent->numChildren - 1]) {
			// 打印错误信息，内存分配失败
			printf("内存分配失败。\n");
			exit(EXIT_FAILURE);
		}

		// 打印成功信息
		printf("%s 已添加为 %s 的孩子。\n", child->name, parentName);
		addMember(familyTree, child);
	} else {
		// 打印未找到父亲/母亲的信息
		printf("未找到名为 '%s' 的父母。\n", parentName);

		// 释放孩子成员的内存
		freeMember(child);
	}
}

// 释放成员内存
void freeMember(FamilyMember *member) {
	// 检查成员指针是否为NULL
	if (member) {
		// 使用free函数释放成员各个字段的内存空间
		free(member->name);
		free(member->birthdate);
		free(member->maritalStatus);
		free(member->address);
		free(member->deathDate);

		// 检查孩子列表是否为空
		if (member->children != NULL) {
			// 循环释放孩子列表中每个孩子的内存空间
			for (int i = 0; i < member->numChildren; i++) {
				free(member->children[i]);
			}
			// 释放孩子列表的内存空间
			free(member->children);
		}

		// 最后释放成员结构体的内存空间
		free(member);
	}
}

// 添加成员
void addMember(FamilyTree *familyTree, FamilyMember *member) {
	// 检查参数是否为NULL
	if (!familyTree || !member) {
		// 打印错误信息，提示参数错误
		printf("参数错误。\n");
		// 返回函数调用点
		return;
	}

	// 检查家谱成员数量是否已达到最大值
	if (familyTree->numMembers < MAX_MEMBERS) {
		// 将新成员添加到家谱成员数组中
		familyTree->members[familyTree->numMembers] = member;
		// 增加家谱成员数量
		familyTree->numMembers++;
	} else {
		// 如果家谱成员已满，打印错误信息，提示无法添加更多成员
		printf("家谱成员已满，无法添加更多成员。\n");
		// 释放新成员的内存空间
		freeMember(member);
	}
}


// 显示特定代成员的信息
void displayGeneration(const FamilyTree *familyTree, int generation) {
	// 打印特定代成员的信息
	printf("第 %d 代 成员：\n", generation);

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; ++i) {
		// 如果成员的代数与指定代数相符，打印成员信息
		if (familyTree->members[i]->generation == generation) {
			printf("%s（出生日期：%s）\n", familyTree->members[i]->name, familyTree->members[i]->birthdate);
		}
	}
	// 打印换行符，增加可读性
	printf("\n");
}

// 按姓名查询
FamilyMember *searchByName(const FamilyTree *familyTree, const char *name) {
	// 检查参数是否为NULL
	if (!familyTree || !name) {
		// 打印错误信息，提示参数错误
		printf("参数错误。\n");
		// 返回NULL表示未找到
		return NULL;
	}

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; i++) {
		// 如果成员姓名与查询姓名匹配，返回该成员指针
		if (strcmp(familyTree->members[i]->name, name) == 0) {
			return familyTree->members[i];
		}
	}

	// 如果未找到匹配的成员，返回NULL
	return NULL;
}



// 按出生日期查询
void searchByBirthdate(const FamilyTree *familyTree, const char *birthdate) {
	// 检查参数是否为NULL
	if (!familyTree || !birthdate) {
		// 打印错误信息，提示参数错误
		printf("参数错误。\n");
		// 返回函数调用点
		return;
	}

	// 打印出生日期为指定日期的成员信息
	printf("出生日期为 %s 的成员：\n", birthdate);

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; i++) {
		// 如果成员的出生日期与查询日期匹配，打印成员姓名
		if (strcmp(familyTree->members[i]->birthdate, birthdate) == 0) {
			printf("- %s\n", familyTree->members[i]->name);
		}
	}
}

// 辅助函数，根据姓名查找成员的上一代（父亲）
FamilyMember *findParent(const FamilyTree *familyTree, const FamilyMember *member) {
	// 检查参数是否为NULL
	if (!familyTree || !member) {
		// 返回NULL表示未找到
		return NULL;
	}

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; i++) {
		// 如果当前成员有孩子
		if (familyTree->members[i]->numChildren > 0) {
			// 遍历当前成员的孩子列表
			for (int j = 0; j < familyTree->members[i]->numChildren; j++) {
				// 如果孩子的姓名与目标成员姓名匹配，返回当前成员（父亲）
				if (strcmp(familyTree->members[i]->children[j], member->name) == 0) {
					return familyTree->members[i];
				}
			}
		}
	}
	// 如果未找到父亲，返回NULL
	return NULL;
}

// 初始化队列
void initQueue(Queue *queue) {
	queue->front = -1;
	queue->rear = -1;
}

// 队列是否为空
int isEmpty(const Queue *queue) {
	return (queue->front == -1);
}

// 队列是否已满
int isFull(const Queue *queue) {
	return ((queue->front == 0 && queue->rear == MAX_MEMBERS - 1) || (queue->front == queue->rear + 1));
}

// 入队
void enqueue(Queue *queue, FamilyMember *member) {
	// 检查队列是否已满
	if (isFull(queue)) {
		// 打印错误信息，提示队列已满，无法入队
		printf("队列已满，无法入队。\n");
		// 退出程序
		exit(EXIT_FAILURE);
	}

	// 如果队列为空，设置队头和队尾为0
	if (isEmpty(queue)) {
		queue->front = 0;
		queue->rear = 0;
	} else if (queue->rear == MAX_MEMBERS - 1) {
		// 如果队尾已到达队列末尾，将队尾设置为0
		queue->rear = 0;
	} else {
		// 队尾后移
		queue->rear++;
	}

	// 将成员指针放入队列的队尾位置
	queue->data[queue->rear] = member;
}

// 出队
FamilyMember *dequeue(Queue *queue) {
	// 检查队列是否为空
	if (isEmpty(queue)) {
		// 打印错误信息，提示队列为空，无法出队
		printf("队列为空，无法出队。\n");
		// 退出程序
		exit(EXIT_FAILURE);
	}

	// 获取队头成员指针
	FamilyMember *member = queue->data[queue->front];

	// 如果队列中只有一个元素
	if (queue->front == queue->rear) {
		queue->front = -1;
		queue->rear = -1;
	} else if (queue->front == MAX_MEMBERS - 1) {
		// 如果队头已到达队列末尾，将队头设置为0
		queue->front = 0;
	} else {
		// 队头后移
		queue->front++;
	}

	// 返回出队的成员指针
	return member;
}


// 辅助函数，根据姓名查找成员在家谱中的索引
int findIndexByName(const FamilyTree *familyTree, const char *name) {
	// 检查参数是否为NULL
	if (!familyTree || !name) {
		// 返回-1表示未找到
		return -1;
	}

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; i++) {
		// 如果成员姓名与查询姓名匹配，返回成员在数组中的索引
		if (strcmp(familyTree->members[i]->name, name) == 0) {
			return i;
		}
	}

	// 如果未找到匹配的成员，返回-1
	return -1;
}

// 递归删除成员及其后代
void removeMemberRecursively(FamilyTree *familyTree, FamilyMember *member) {
	// 检查参数是否为NULL
	if (!familyTree || !member) {
		// 返回
		return;
	}

	// 初始化队列
	Queue queue;
	initQueue(&queue);

	// 先将当前成员入队
	enqueue(&queue, member);

	// 遍历队列
	while (!isEmpty(&queue)) {
		// 出队一个成员
		FamilyMember *currentMember = dequeue(&queue);

		// 遍历当前成员的所有孩子，并将其入队
		for (int i = 0; i < currentMember->numChildren; i++) {
			// 根据孩子姓名查找孩子成员
			FamilyMember *child = searchByName(familyTree, currentMember->children[i]);

			// 如果孩子成员存在，将其入队
			if (child) {
				enqueue(&queue, child);
			}
		}

		// 从父亲/母亲的孩子列表中移除
		FamilyMember *parent = findParent(familyTree, currentMember);

		// 如果找到父亲/母亲
		if (parent) {
			// 遍历父亲/母亲的孩子列表
			for (int i = 0; i < parent->numChildren; i++) {
				// 找到当前成员在父亲/母亲孩子列表中的位置
				if (strcmp(parent->children[i], currentMember->name) == 0) {
					// 释放当前成员在父亲/母亲孩子列表中的空间
					free(parent->children[i]);

					// 将后面的孩子依次向前移动一个位置
					for (int j = i; j < parent->numChildren - 1; j++) {
						parent->children[j] = parent->children[j + 1];
					}

					// 更新父亲/母亲的孩子数量
					parent->numChildren--;
					break;
				}
			}
		}


		// 从家谱中移除
		int index = findIndexByName(familyTree, currentMember->name);

		// 如果找到成员在家谱中的位置
		if (index != -1) {
			// 释放当前成员的内存
			freeMember(familyTree->members[index]);

			// 将后面的成员依次向前移动一个位置
			for (int i = index; i < familyTree->numMembers - 1; i++) {
				familyTree->members[i] = familyTree->members[i + 1];
			}

			// 更新家谱成员数量
			familyTree->numMembers--;
		}
	}
}


// 移除成员及其后代
void removeMember(FamilyTree *familyTree, const char *name) {
	// 检查参数是否为NULL
	if (!familyTree || !name) {
		// 打印错误信息，参数错误
		printf("参数错误。\n");
		return;
	}

	// 根据姓名查找成员
	FamilyMember *member = searchByName(familyTree, name);

	// 如果成员存在
	if (member) {
		// 调用递归删除函数
		removeMemberRecursively(familyTree, member);

		// 打印移除成功的信息
		printf("%s 及其后代已从家谱中移除。\n", name);
	} else {
		// 打印未找到成员的信息
		printf("未找到名为 '%s' 的成员。\n", name);
	}
}


// 添加孩子
void addChild2(FamilyTree *familyTree, const char *parentName, FamilyMember *child) {
	// 打印调试信息
	printf("Adding child %s to parent %s in addChild function\n", child->name, parentName);

	// 检查参数是否为NULL
	if (!familyTree || !parentName || !child) {
		// 打印错误信息，参数错误
		printf("参数错误。\n");
		return;
	}

	// 根据父亲/母亲姓名查找父亲/母亲成员
	FamilyMember *parent = searchByName(familyTree, parentName);

	// 如果父亲/母亲存在
	if (parent) {
		// 增加父亲/母亲的孩子数量
		parent->numChildren++;

		// 重新分配父亲/母亲的孩子列表的内存
		parent->children = (char **)realloc(parent->children, sizeof(char *) * parent->numChildren);
		if (!parent->children) {
			// 打印错误信息，内存分配失败
			printf("内存分配失败。\n");
			exit(EXIT_FAILURE);
		}

		// 将孩子姓名添加到父亲/母亲的孩子列表中
		parent->children[parent->numChildren - 1] = child->name ? strdup(child->name) : NULL;
		if (!parent->children[parent->numChildren - 1]) {
			// 打印错误信息，内存分配失败
			printf("内存分配失败。\n");
			exit(EXIT_FAILURE);
		}

		// 打印成功信息
		printf("%s 已添加为 %s 的孩子。\n", child->name, parentName);
	} else {
		// 打印未找到父亲/母亲的信息
		printf("未找到名为 '%s' 的父母。\n", parentName);

		// 释放孩子成员的内存
		freeMember(child);
	}
}


// 释放家庭成员的内存
void freeFamilyTree(FamilyTree *familyTree) {
	// 检查参数是否为NULL
	if (!familyTree) {
		// 打印错误信息，参数错误
		printf("参数错误。\n");
		return;
	}

	// 遍历家谱成员数组
	for (int i = 0; i < familyTree->numMembers; i++) {
		// 释放成员的内存
		freeMember(familyTree->members[i]);
		// 将数组中的成员指针置为NULL，避免悬空指针
		familyTree->members[i] = NULL;
	}
}



