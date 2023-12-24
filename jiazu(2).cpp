#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������
#define MAX_MEMBERS 100

// ��ͥ��Ա�ṹ��
typedef struct {
	char *name;             // ��Ա����
	char *birthdate;        // ��������
	char *maritalStatus;    // ����״��
	char *address;          // ��ַ
	int alive;              // �Ƿ���
	char *deathDate;        // ��������
	char **children;        // ������������
	int numChildren;        // ��������
	int generation;         // ��Ա�����Ĵ���
} FamilyMember;

// ���׽ṹ��
typedef struct {
	FamilyMember *members[MAX_MEMBERS]; // ���г�Ա
	int numMembers;                      // ��Ա����
} FamilyTree;

// ���нṹ��
typedef struct {
	FamilyMember *data[MAX_MEMBERS];
	int front;
	int rear;
} Queue;

// ����������
//��ʼ�������Ա
FamilyMember *createMember(const char *name, const char *birthdate, const char *maritalStatus, const char *address,
                           int alive, const char *deathDate);
//��ӳ�Ա
void addMember(FamilyTree *familyTree, FamilyMember *member);
//��ʾ����ڼ���
void displayGeneration(const FamilyTree *familyTree, int generation);
//��������Ѱ����Ϣ
FamilyMember *searchByName(const FamilyTree *familyTree, const char *name);
//��������Ѱ������
void searchByBirthdate(const FamilyTree *familyTree, const char *birthdate);
//��Ӻ���
void addChild(FamilyTree *familyTree, const char *parentName, FamilyMember *child);
//�ͷż����Ա��̬�ڴ�ռ�
void freeMember(FamilyMember *member);
//�ͷż��׶�̬�ڴ�ռ�
void freeFamilyTree(FamilyTree *familyTree);

// ���������������������ҳ�Ա����һ�������ף�
FamilyMember *findParent(const FamilyTree *familyTree, const FamilyMember *member) ;
// ��ʼ������
void initQueue(Queue *queue) ;
// �����Ƿ�Ϊ��
int isEmpty(const Queue *queue) ;
// �����Ƿ�����
int isFull(const Queue *queue) ;
// ���
void enqueue(Queue *queue, FamilyMember *member);
// ����
FamilyMember *dequeue(Queue *queue);
// ���������������������ҳ�Ա�ڼ����е�����
int findIndexByName(const FamilyTree *familyTree, const char *name) ;
// �ݹ�ɾ����Ա������
void removeMemberRecursively(FamilyTree *familyTree, FamilyMember *member) ;
// �Ƴ���Ա������
void removeMember(FamilyTree *familyTree, const char *name) ;
// �޸ĺ�����Ϣ
void addChild2(FamilyTree *familyTree, const char *parentName, FamilyMember *child) ;

int main() {
	FamilyTree familyTree;
	familyTree.numMembers = 0;
	// �������30����Ա������
	// 1 ��
	FamilyMember *member1 = createMember("үү", "1900-01-01", "δ��", "����", 0, "1980-01-01");
	member1->generation = 1;
	addMember(&familyTree, member1);

	// 2 ��
	FamilyMember *member2 = createMember("�ְ�", "1930-01-01", "�ѻ�", "����", 0, "1990-01-01");
	member2->generation = 2;
	addChild(&familyTree, "үү", member2);

	FamilyMember *member3 = createMember("�Ϲ�", "1935-01-01", "�ѻ�", "�Ϻ�", 1, "");
	member3->generation = 2;
	addChild(&familyTree, "үү", member3);

	FamilyMember *member4 = createMember("����", "1955-01-01", "δ��", "����", 1, "");
	member4->generation = 2;
	addChild(&familyTree, "үү", member4);

	FamilyMember *member5 = createMember("����", "1960-01-01", "�ѻ�", "�Ϻ�", 1, "");
	member5->generation = 2;
	addChild(&familyTree, "үү", member5);

	FamilyMember *member6 = createMember("�ְֵ��ֵ�", "1950-01-01", "�ѻ�", "����", 1, "");
	member6->generation = 2;
	addChild(&familyTree, "үү", member6);

	FamilyMember *member7 = createMember("�ְֵĽ���", "1952-01-01", "�ѻ�", "����", 1, "");
	member7->generation = 2;
	addChild(&familyTree, "үү", member7);

	// 3 ��
	FamilyMember *member8 = createMember("����Ķ���1", "1980-01-01", "δ��", "����", 1, "");
	member8->generation = 3;
	addChild(&familyTree, "����", member8);

	FamilyMember *member9 = createMember("����Ķ���2", "1982-01-01", "δ��", "����", 1, "");
	member9->generation = 3;
	addChild(&familyTree, "����", member9);

	FamilyMember *member10 = createMember("���̵�Ů��1", "1985-01-01", "δ��", "�Ϻ�", 1, "");
	member10->generation = 3;
	addChild(&familyTree, "����", member10);

	FamilyMember *member11 = createMember("���̵�Ů��2", "1988-01-01", "δ��", "�Ϻ�", 1, "");
	member11->generation = 3;
	addChild(&familyTree, "����", member11);

	// 4 ��
	FamilyMember *member12 = createMember("���������1", "2005-01-01", "δ��", "����", 1, "");
	member12->generation = 4;
	addChild(&familyTree, "����Ķ���1", member12);

	FamilyMember *member13 = createMember("���������2", "2008-01-01", "δ��", "����", 1, "");
	member13->generation = 4;
	addChild(&familyTree, "����Ķ���1", member13);

	FamilyMember *member14 = createMember("���̵�����Ů1", "2010-01-01", "δ��", "�Ϻ�", 1, "");
	member14->generation = 4;
	addChild(&familyTree, "���̵�Ů��1", member14);

	FamilyMember *member15 = createMember("���̵�����Ů2", "2012-01-01", "δ��", "�Ϻ�", 1, "");
	member15->generation = 4;
	addChild(&familyTree, "���̵�Ů��2", member15);
	int choice;
	while (1) {
		printf("\n���׹���ϵͳ��\n");
		printf("1. ��ʾĳһ����Ա\n");
		printf("2. ��������ѯ\n");
		printf("3. ���������ڲ�ѯ\n");
		printf("4. ��Ӻ���\n");
		printf("5. �Ƴ���Ա\n");
		printf("6. �޸ĳ�Ա��Ϣ\n");
		printf("7. �˳�\n");

		printf("����������ѡ��1-7����");
		if (scanf("%d", &choice) != 1) {
			scanf("%*[^\n]");
			printf("�������������һ�����֡�\n");
			continue;
		}

		switch (choice) {
			// ���1���û�����һ����������ʾ�ô��ļ�����Ϣ
			case 1: {
				// ����һ�����ͱ������ڴ洢�û�����Ĵ���
				int generation;
				// ��ʾ�û��������
				printf("�����������");
				// ʹ��scanf�������Զ�ȡ�û�����Ĵ������������ֵ��Ϊ1��˵�����벻��һ����Ч������
				if (scanf("%d", &generation) != 1) {
					// ��ӡ������Ϣ������ʾ�û�����һ������
					printf("�������������һ�����֡�\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}
				// ����displayGeneration��������ʾָ�������ļ�����Ϣ
				displayGeneration(&familyTree, generation);
				// ������ǰ����Ĵ�������ִ����һ�����
				break;
			}
			// ���2����������ѯ���׳�Ա��Ϣ
			case 2: {
				// ����һ���ַ��������ڴ洢�û����������
				char name[50];
				// ��ʾ�û�����Ҫ��ѯ������
				printf("������Ҫ��ѯ��������");
				// ʹ��scanf�������Զ�ȡ�û�������������������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", name) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ������
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}
				// ����searchByName���������������ڼ����в��ҳ�Ա
				FamilyMember *member = searchByName(&familyTree, name);
				// ����ҵ���Ա
				if (member) {
					// ��ʾ��Ա�Ļ�����Ϣ
					printf("\n%s ����ϸ��Ϣ��\n", name);
					printf("������%s\n", member->name);
					printf("�������ڣ�%s\n", member->birthdate);
					printf("����״����%s\n", member->maritalStatus);
					printf("��ַ��%s\n", member->address);
					printf("�Ƿ��ڣ�%s\n", member->alive ? "��" : "��");
					// �����Ա�ѹʣ���ʾ��������
					if (!member->alive) {
						printf("�������ڣ�%s\n", member->deathDate);
					}

					// ��ʾ������Ϣ
					FamilyMember *father = findParent(&familyTree, member);
					// ����ҵ�����
					if (father) {
						printf("\n%s �ĸ�����Ϣ��\n", name);
						printf("������%s\n", father->name);
						printf("�������ڣ�%s\n", father->birthdate);
						printf("����״����%s\n", father->maritalStatus);
						printf("��ַ��%s\n", father->address);
						printf("�Ƿ��ڣ�%s\n", father->alive ? "��" : "��");
						// ��������ѹʣ���ʾ��������
						if (!father->alive) {
							printf("�������ڣ�%s\n", father->deathDate);
						}
						// ��ʾ�������ڴ���
						printf("�� %d ��\n", father->generation);
					} else {
						// ���δ�ҵ����ף������ʾ��Ϣ
						printf("\n%s δ�ҵ����ס�\n", name);
					}
					printf("\n");

					// ��ʾ������Ϣ
					if (member->numChildren > 0) {
						printf("�����ǣ�\n");
						// ������Ա�ĺ����б�
						for (int i = 0; i < member->numChildren; i++) {
							// ���ݺ��������ڼ����в��Һ�����Ϣ
							FamilyMember *child = searchByName(&familyTree, member->children[i]);
							// ����ҵ�����
							if (child) {
								// ������ӵ�����
								printf("- %s\n", child->name);
								// ������ӵ���ϸ��Ϣ
								printf("  �������ڣ�%s\n", child->birthdate);
								printf("  ����״����%s\n", child->maritalStatus);
								printf("  ��ַ��%s\n", child->address);
								printf("  �Ƿ��ڣ�%s\n", child->alive ? "��" : "��");
								// ��������ѹʣ���ʾ��������
								if (!child->alive) {
									printf("  �������ڣ�%s\n", child->deathDate);
								}
								// ��ʾ�������ڴ���
								printf("  �� %d ��\n", child->generation);
							}
						}
					} else {
						// ���û�к��ӣ������ʾ��Ϣ
						printf("���޺��ӡ�\n");
					}
				} else {
					// ���δ�ҵ���Ա�������ʾ��Ϣ
					printf("δ�ҵ�����Ϊ '%s' �ĳ�Ա��\n", name);
				}
				// ������ǰ����Ĵ�������ִ����һ�����
				break;
			}


			case 3: {
				// �û�ѡ�����3�����������ڲ�ѯ���׳�Ա��Ϣ

				// ����һ���ַ��������ڴ洢�û�����ĳ�������
				char birthdate[20];
				// ��ʾ�û�����Ҫ��ѯ�ĳ�������
				printf("������Ҫ��ѯ�ĳ������ڣ�");
				// ʹ��scanf�������Զ�ȡ�û�����ĳ������ڣ��������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", birthdate) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĳ�������
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}
				// ����searchByBirthdate���������ݳ��������ڼ����в��ҳ�Ա
				searchByBirthdate(&familyTree, birthdate);
				// ������ǰ����Ĵ�������ִ����һ�����
				break;
			}

			case 4: {
				// �û�ѡ�����4����Ӻ��ӵ�����

				// �����ַ����飬���ڴ洢�û�����ĸ�ĸ�������������������ӳ������ڡ����ӳ�����ַ���Ƿ���
				char parentName[50];
				char childName[50];
				char childBirthdate[20];
				char childBirthloc[50];
				char marryornot[4];

				// ��ʾ�û����븸ĸ������
				printf("�����븸ĸ��������");
				// ʹ��scanf�������Զ�ȡ�û�����ĸ�ĸ�������������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", parentName) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĸ�ĸ����
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ���ݸ�ĸ�����ڼ����в��Ҹ�ĸ��Ϣ
				FamilyMember *parent = searchByName((const FamilyTree *)&familyTree, parentName);

				// ���㺢�����ڴ���
				int childGeneration = parent->generation + 1;

				// ��ʾ�û����뺢�ӵ�����
				printf("�����뺢�ӵ�������");
				// ʹ��scanf�������Զ�ȡ�û�����ĺ����������������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", childName) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĺ�������
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ��ʾ�û����뺢�ӵĳ�������
				printf("�����뺢�ӵĳ������ڣ�");
				// ʹ��scanf�������Զ�ȡ�û�����ĺ��ӳ������ڣ��������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", childBirthdate) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĺ��ӳ�������
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ��ʾ�û����뺢�ӵĳ�����ַ
				printf("�����뺢�ӵĳ�����ַ��");
				// ʹ��scanf�������Զ�ȡ�û�����ĺ��ӳ�����ַ���������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", childBirthloc) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĺ��ӳ�����ַ
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ��ʾ�û����뺢���Ƿ���
				printf("�Ƿ��飿 (��/��): ");
				// ʹ��scanf�������Զ�ȡ�û�������Ƿ�����Ϣ���������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", marryornot) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ���Ƿ�����Ϣ
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ����createMember�����������ӳ�Ա
				FamilyMember *child = createMember(childName, childBirthdate, marryornot, childBirthloc, 1, "");
				// ����addChild������������ӵ�������
				addChild(&familyTree, parentName, child);
				// ���ú������ڴ���
				child->generation = childGeneration;
				// ������ǰ����Ĵ�������ִ����һ�����
				break;

			}

			case 5: {
				// �û�ѡ�����5���Ƴ������еĳ�Ա

				// �����ַ����飬���ڴ洢�û�����ĳ�Ա����
				char memberName[50];
				// ��ʾ�û�����Ҫ�Ƴ��ĳ�Ա����
				printf("������Ҫ�Ƴ��ĳ�Ա������");
				// ʹ��scanf�������Զ�ȡ�û�����ĳ�Ա�������������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", memberName) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĳ�Ա����
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}
				// ����removeMember�������Ӽ������Ƴ�ָ�������ĳ�Ա
				removeMember(&familyTree, memberName);
				// ������ǰ����Ĵ�������ִ����һ�����
				break;
			}
			case 6: {
				// �û�ѡ�����6���޸ļ��׳�Ա��Ϣ

				// �����ַ����飬���ڴ洢�û�����ĳ�Ա�������Ƿ��ڡ��Ƿ��޸ĸ�ĸ��ϵ���Ƿ��޸ĺ��ӹ�ϵ
				char memberName[50];
				char deadornot[8];
				char yesorno[8];

				// ��ʾ�û�����Ҫ�޸���Ϣ�ĳ�Ա����
				printf("������Ҫ�޸���Ϣ�ĳ�Ա������");
				// ʹ��scanf�������Զ�ȡ�û�����ĳ�Ա�������������ֵ��Ϊ1��˵�����벻�Ϸ�
				if (scanf("%s", memberName) != 1) {
					// ��ӡ������Ϣ������ʾ�û�������ȷ�ĳ�Ա����
					printf("�������\n");
					// ������ǰ����Ĵ�������ִ����һ�����
					break;
				}

				// ���ݳ�Ա�����ڼ����в��ҳ�Ա��Ϣ
				FamilyMember *member = searchByName(&familyTree, memberName);
				char originalName[50]; // ��ʱ�洢ԭʼ���ֵ�����

				// ����ԭʼ����
				strcpy(originalName, member->name);
				//Ѱ�Ҹ���
				FamilyMember *oldParent = findParent(&familyTree, member);
				// ����ҵ���Ա
				if (member) {
					// ��ʾ�û������µ�����
					printf("�������µ�������");
					// ʹ��scanf�������Զ�ȡ�û���������������������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", member->name) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ��������
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ��ʾ�û������µĳ�������
					printf("�������µĳ������ڣ�");
					// ʹ��scanf�������Զ�ȡ�û�������³������ڣ��������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", member->birthdate) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���³�������
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ��ʾ�û������µĻ���״��
					printf("�������µĻ���״����");
					// ʹ��scanf�������Զ�ȡ�û�������»���״�����������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", member->maritalStatus) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���»���״��
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ��ʾ�û������µĵ�ַ
					printf("�������µĵ�ַ��");
					// ʹ��scanf�������Զ�ȡ�û�������µ�ַ���������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", member->address) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���µ�ַ
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ��ʾ�û������Ա�Ƿ���
					printf("��Ա�Ƿ��ڣ�����/�񣩣�");
					// ʹ��scanf�������Զ�ȡ�û�������Ƿ�����Ϣ���������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", deadornot) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���Ƿ�����Ϣ
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// �����û�������³�Ա�Ƿ��ڵ�״̬
					if (strcmp(deadornot, "��") == 0) {
						member->alive = 0;
						// ��ʾ�û�������������
						printf("�������������ڣ�");
						// ʹ��scanf�������Զ�ȡ�û�������������ڣ��������ֵ��Ϊ1��˵�����벻�Ϸ�
						if (scanf("%s", member->deathDate) != 1) {
							// ��ӡ������Ϣ������ʾ�û�������ȷ����������
							printf("�������\n");
							// ������ǰ����Ĵ�������ִ����һ�����
							break;
						}
					} else {
						member->alive = 1;
					}

					// ��ʾ�û��Ƿ���Ҫ�޸ĸ�ĸ��ϵ
					printf("�Ƿ���Ҫ�޸ĸ�ĸ�Ĺ�ϵ�� (��/��): ");
					// ʹ��scanf�������Զ�ȡ�û�������Ƿ��޸ĸ�ĸ��ϵ����Ϣ���������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", yesorno) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���Ƿ��޸ĸ�ĸ��ϵ����Ϣ
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ����û�ѡ���ǣ���ʾ�û������µĸ���/ĸ�׵�����
					if (strcmp(yesorno, "��") == 0) {
						char newParentName[50];
						printf("�������µĸ���/ĸ�׵�������");
						// ʹ��scanf�������Զ�ȡ�û�������¸���/ĸ���������������ֵ��Ϊ1��˵�����벻�Ϸ�
						if (scanf("%s", newParentName) != 1) {
							// ��ӡ������Ϣ������ʾ�û�������ȷ���¸���/ĸ������
							printf("�������\n");
							// ������ǰ����Ĵ�������ִ����һ�����
							break;
						}
						// �Ƴ���ǰ��ĸ��ϵ
						FamilyMember *oldParent = findParent(&familyTree, member);

						// ����ҵ���ǰ��ĸ
						if (oldParent) {
							// ������ĸ�ĺ����б�
							for (int i = 0; i < oldParent->numChildren; i++) {
								// �ҵ����Ա����ƥ��ĺ���
								if (strcmp(oldParent->children[i], member->name) == 0) {
									// �ͷź��ӵ��ڴ�ռ�
									free(oldParent->children[i]);
									// �ƶ�����Ԫ�أ�ɾ����ǰ����
									for (int j = i; j < oldParent->numChildren - 1; j++) {
										oldParent->children[j] = oldParent->children[j + 1];
									}
									// ���ٸ�ĸ�ĺ�������
									oldParent->numChildren--;
									// �ҵ�ƥ������˳�ѭ��
									break;
								}
							}
						}
						// ����µĸ�ĸ��ϵ
						FamilyMember *newParent = searchByName(&familyTree, newParentName);

						// ����ҵ��µĸ���/ĸ��
						if (newParent) {
							// ����addChild2����������Ա���Ϊ�¸���/ĸ�׵ĺ���
							addChild2(&familyTree, newParentName, member);
							// ��ӡ��ʾ��Ϣ����ʾ��ĸ��ϵ�Ѹ���
							printf("%s �ĸ�ĸ��ϵ�Ѹ��¡�\n", member->name);
						} else {
							// ���δ�ҵ��µĸ���/ĸ�ף���ӡ��ʾ��Ϣ
							printf("δ�ҵ���Ϊ '%s' �ĸ���/ĸ�ס�\n", newParentName);
						}
					}
					// ����û�ѡ�����ʾ�û���֮ǰ��ĸ��ϵ��
					else {
						// �û�ѡ���޸ĸ�ĸ��ϵ�����
						// ���֮ǰ�и�ĸ��ϵ����֮ǰ�ĸ�ĸ�ĺ������ָ���Ϊ���ڵ�����

						if (oldParent) {
							for (int i = 0; i < oldParent->numChildren; i++) {
								if (strcmp(oldParent->children[i], originalName) == 0) {
									// �ͷ�֮ǰ�ĺ�������
									free(oldParent->children[i]);
									// �����µĺ������֣������Ƴ�Ա������
									oldParent->children[i] = strdup(member->name);
									if (!oldParent->children[i]) {
										// �ڴ����ʧ�ܵĴ����߼�
										printf("�ڴ����ʧ�ܡ�\n");
										exit(EXIT_FAILURE);
									}
									// �ҵ�ƥ������˳�ѭ��
									break;
								}
							}
						}
					}


					// ��ʾ�û��Ƿ���Ҫ�޸ĺ��ӹ�ϵ
					printf("�Ƿ���Ҫ�޸ĺ��ӵĹ�ϵ�� (��/��): ");
					// ʹ��scanf�������Զ�ȡ�û�������Ƿ��޸ĺ��ӹ�ϵ����Ϣ���������ֵ��Ϊ1��˵�����벻�Ϸ�
					if (scanf("%s", yesorno) != 1) {
						// ��ӡ������Ϣ������ʾ�û�������ȷ���Ƿ��޸ĺ��ӹ�ϵ����Ϣ
						printf("�������\n");
						// ������ǰ����Ĵ�������ִ����һ�����
						break;
					}

					// ����û�ѡ���ǣ���ʾ�û������µĺ�������
					if (strcmp(yesorno, "��") == 0) {
						char newChildName[50];
						printf("�������µĺ��ӵ�������");
						// ʹ��scanf�������Զ�ȡ�û�������º����������������ֵ��Ϊ1��˵�����벻�Ϸ�
						if (scanf("%s", newChildName) != 1) {
							// ��ӡ������Ϣ������ʾ�û�������ȷ���º�������
							printf("�������\n");
							// ������ǰ����Ĵ�������ִ����һ�����
							break;
						}

						// �Ƴ���ǰ���ӹ�ϵ
						for (int i = 0; i < member->numChildren; i++) {
							// �ҵ����º�������ƥ��ĺ���
							if (strcmp(member->children[i], newChildName) == 0) {
								// �ͷź��ӵ��ڴ�ռ�
								free(member->children[i]);
								// �ƶ�����Ԫ�أ�ɾ����ǰ����
								for (int j = i; j < member->numChildren - 1; j++) {
									member->children[j] = member->children[j + 1];
								}
								// ���ٳ�Ա�ĺ�������
								member->numChildren--;
								// �ҵ�ƥ������˳�ѭ��
								break;
							}
						}

						// ����µĺ��ӹ�ϵ
						FamilyMember *newChild = searchByName(&familyTree, newChildName);

						// ����ҵ��µĺ���
						if (newChild) {
							// ����addChild2���������º������Ϊ��Ա�ĺ���
							addChild2(&familyTree, member->name, newChild);
							// ��ӡ��ʾ��Ϣ����ʾ���ӹ�ϵ�Ѹ���
							printf("%s �ĺ��ӹ�ϵ�Ѹ��¡�\n", member->name);
						} else {
							// ���δ�ҵ��µĺ��ӣ���ӡ��ʾ��Ϣ
							printf("δ�ҵ���Ϊ '%s' �ĺ��ӡ�\n", newChildName);
						}
					}
				} else {
					// ���δ�ҵ���Ա�������ʾ��Ϣ
					printf("δ�ҵ���Ϊ '%s' �ĳ�Ա��\n", memberName);
				}
				// ������ǰ����Ĵ�������ִ����һ�����
				break;

			}
			case 7: {
				printf("�˳����׹���ϵͳ��\n");
				exit(0);
				freeFamilyTree(&familyTree); // �ͷż����ڴ�
			}
			default: {
				printf("��Ч��ѡ��������1��7֮������֡�\n");
				continue;
			}

		}
	}
	return 0;
}

// ������Ա
FamilyMember *createMember(const char *name, const char *birthdate, const char *maritalStatus, const char *address,

                           int alive, const char *deathDate) {
	// �����ڴ�ռ䣬���ڴ洢FamilyMember�ṹ��
	FamilyMember *member = (FamilyMember *)calloc(1, sizeof(FamilyMember));
	// ����ڴ�����Ƿ�ɹ�
	if (!member) {
		// �������ʧ�ܣ���ӡ������Ϣ�����˳�����
		printf("�ڴ����ʧ�ܡ�\n");
		exit(EXIT_FAILURE);
	}

	// ʹ��strdup���������ַ����������µ��ڴ�ռ䣬����ָ�빲��
	member->name = name ? strdup(name) : NULL;
	member->birthdate = birthdate ? strdup(birthdate) : NULL;
	member->maritalStatus = maritalStatus ? strdup(maritalStatus) : NULL;
	member->address = address ? strdup(address) : NULL;
	member->alive = alive;
	member->deathDate = deathDate ? strdup(deathDate) : NULL;
	member->numChildren = 0;
	member->children = NULL;

	// ���ش����ĳ�Ա�ṹ��ָ��
	return member;
}

// ��Ӻ���
void addChild(FamilyTree *familyTree, const char *parentName, FamilyMember *child) {
	// ��ӡ������Ϣ
	printf("Adding child %s to parent %s in addChild function\n", child->name, parentName);

	// �������Ƿ�ΪNULL
	if (!familyTree || !parentName || !child) {
		// ��ӡ������Ϣ����������
		printf("��������\n");
		return;
	}

	// ���ݸ���/ĸ���������Ҹ���/ĸ�׳�Ա
	FamilyMember *parent = searchByName(familyTree, parentName);

	// �������/ĸ�״���
	if (parent) {
		// ���Ӹ���/ĸ�׵ĺ�������
		parent->numChildren++;

		// ���·��丸��/ĸ�׵ĺ����б���ڴ�
		parent->children = (char **)realloc(parent->children, sizeof(char *) * parent->numChildren);
		if (!parent->children) {
			// ��ӡ������Ϣ���ڴ����ʧ��
			printf("�ڴ����ʧ�ܡ�\n");
			exit(EXIT_FAILURE);
		}

		// ������������ӵ�����/ĸ�׵ĺ����б���
		parent->children[parent->numChildren - 1] = child->name ? strdup(child->name) : NULL;
		if (!parent->children[parent->numChildren - 1]) {
			// ��ӡ������Ϣ���ڴ����ʧ��
			printf("�ڴ����ʧ�ܡ�\n");
			exit(EXIT_FAILURE);
		}

		// ��ӡ�ɹ���Ϣ
		printf("%s �����Ϊ %s �ĺ��ӡ�\n", child->name, parentName);
		addMember(familyTree, child);
	} else {
		// ��ӡδ�ҵ�����/ĸ�׵���Ϣ
		printf("δ�ҵ���Ϊ '%s' �ĸ�ĸ��\n", parentName);

		// �ͷź��ӳ�Ա���ڴ�
		freeMember(child);
	}
}

// �ͷų�Ա�ڴ�
void freeMember(FamilyMember *member) {
	// ����Աָ���Ƿ�ΪNULL
	if (member) {
		// ʹ��free�����ͷų�Ա�����ֶε��ڴ�ռ�
		free(member->name);
		free(member->birthdate);
		free(member->maritalStatus);
		free(member->address);
		free(member->deathDate);

		// ��麢���б��Ƿ�Ϊ��
		if (member->children != NULL) {
			// ѭ���ͷź����б���ÿ�����ӵ��ڴ�ռ�
			for (int i = 0; i < member->numChildren; i++) {
				free(member->children[i]);
			}
			// �ͷź����б���ڴ�ռ�
			free(member->children);
		}

		// ����ͷų�Ա�ṹ����ڴ�ռ�
		free(member);
	}
}

// ��ӳ�Ա
void addMember(FamilyTree *familyTree, FamilyMember *member) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !member) {
		// ��ӡ������Ϣ����ʾ��������
		printf("��������\n");
		// ���غ������õ�
		return;
	}

	// �����׳�Ա�����Ƿ��Ѵﵽ���ֵ
	if (familyTree->numMembers < MAX_MEMBERS) {
		// ���³�Ա��ӵ����׳�Ա������
		familyTree->members[familyTree->numMembers] = member;
		// ���Ӽ��׳�Ա����
		familyTree->numMembers++;
	} else {
		// ������׳�Ա��������ӡ������Ϣ����ʾ�޷���Ӹ����Ա
		printf("���׳�Ա�������޷���Ӹ����Ա��\n");
		// �ͷ��³�Ա���ڴ�ռ�
		freeMember(member);
	}
}


// ��ʾ�ض�����Ա����Ϣ
void displayGeneration(const FamilyTree *familyTree, int generation) {
	// ��ӡ�ض�����Ա����Ϣ
	printf("�� %d �� ��Ա��\n", generation);

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; ++i) {
		// �����Ա�Ĵ�����ָ�������������ӡ��Ա��Ϣ
		if (familyTree->members[i]->generation == generation) {
			printf("%s���������ڣ�%s��\n", familyTree->members[i]->name, familyTree->members[i]->birthdate);
		}
	}
	// ��ӡ���з������ӿɶ���
	printf("\n");
}

// ��������ѯ
FamilyMember *searchByName(const FamilyTree *familyTree, const char *name) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !name) {
		// ��ӡ������Ϣ����ʾ��������
		printf("��������\n");
		// ����NULL��ʾδ�ҵ�
		return NULL;
	}

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; i++) {
		// �����Ա�������ѯ����ƥ�䣬���ظó�Աָ��
		if (strcmp(familyTree->members[i]->name, name) == 0) {
			return familyTree->members[i];
		}
	}

	// ���δ�ҵ�ƥ��ĳ�Ա������NULL
	return NULL;
}



// ���������ڲ�ѯ
void searchByBirthdate(const FamilyTree *familyTree, const char *birthdate) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !birthdate) {
		// ��ӡ������Ϣ����ʾ��������
		printf("��������\n");
		// ���غ������õ�
		return;
	}

	// ��ӡ��������Ϊָ�����ڵĳ�Ա��Ϣ
	printf("��������Ϊ %s �ĳ�Ա��\n", birthdate);

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; i++) {
		// �����Ա�ĳ����������ѯ����ƥ�䣬��ӡ��Ա����
		if (strcmp(familyTree->members[i]->birthdate, birthdate) == 0) {
			printf("- %s\n", familyTree->members[i]->name);
		}
	}
}

// ���������������������ҳ�Ա����һ�������ף�
FamilyMember *findParent(const FamilyTree *familyTree, const FamilyMember *member) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !member) {
		// ����NULL��ʾδ�ҵ�
		return NULL;
	}

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; i++) {
		// �����ǰ��Ա�к���
		if (familyTree->members[i]->numChildren > 0) {
			// ������ǰ��Ա�ĺ����б�
			for (int j = 0; j < familyTree->members[i]->numChildren; j++) {
				// ������ӵ�������Ŀ���Ա����ƥ�䣬���ص�ǰ��Ա�����ף�
				if (strcmp(familyTree->members[i]->children[j], member->name) == 0) {
					return familyTree->members[i];
				}
			}
		}
	}
	// ���δ�ҵ����ף�����NULL
	return NULL;
}

// ��ʼ������
void initQueue(Queue *queue) {
	queue->front = -1;
	queue->rear = -1;
}

// �����Ƿ�Ϊ��
int isEmpty(const Queue *queue) {
	return (queue->front == -1);
}

// �����Ƿ�����
int isFull(const Queue *queue) {
	return ((queue->front == 0 && queue->rear == MAX_MEMBERS - 1) || (queue->front == queue->rear + 1));
}

// ���
void enqueue(Queue *queue, FamilyMember *member) {
	// �������Ƿ�����
	if (isFull(queue)) {
		// ��ӡ������Ϣ����ʾ�����������޷����
		printf("�����������޷���ӡ�\n");
		// �˳�����
		exit(EXIT_FAILURE);
	}

	// �������Ϊ�գ����ö�ͷ�Ͷ�βΪ0
	if (isEmpty(queue)) {
		queue->front = 0;
		queue->rear = 0;
	} else if (queue->rear == MAX_MEMBERS - 1) {
		// �����β�ѵ������ĩβ������β����Ϊ0
		queue->rear = 0;
	} else {
		// ��β����
		queue->rear++;
	}

	// ����Աָ�������еĶ�βλ��
	queue->data[queue->rear] = member;
}

// ����
FamilyMember *dequeue(Queue *queue) {
	// �������Ƿ�Ϊ��
	if (isEmpty(queue)) {
		// ��ӡ������Ϣ����ʾ����Ϊ�գ��޷�����
		printf("����Ϊ�գ��޷����ӡ�\n");
		// �˳�����
		exit(EXIT_FAILURE);
	}

	// ��ȡ��ͷ��Աָ��
	FamilyMember *member = queue->data[queue->front];

	// ���������ֻ��һ��Ԫ��
	if (queue->front == queue->rear) {
		queue->front = -1;
		queue->rear = -1;
	} else if (queue->front == MAX_MEMBERS - 1) {
		// �����ͷ�ѵ������ĩβ������ͷ����Ϊ0
		queue->front = 0;
	} else {
		// ��ͷ����
		queue->front++;
	}

	// ���س��ӵĳ�Աָ��
	return member;
}


// ���������������������ҳ�Ա�ڼ����е�����
int findIndexByName(const FamilyTree *familyTree, const char *name) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !name) {
		// ����-1��ʾδ�ҵ�
		return -1;
	}

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; i++) {
		// �����Ա�������ѯ����ƥ�䣬���س�Ա�������е�����
		if (strcmp(familyTree->members[i]->name, name) == 0) {
			return i;
		}
	}

	// ���δ�ҵ�ƥ��ĳ�Ա������-1
	return -1;
}

// �ݹ�ɾ����Ա������
void removeMemberRecursively(FamilyTree *familyTree, FamilyMember *member) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !member) {
		// ����
		return;
	}

	// ��ʼ������
	Queue queue;
	initQueue(&queue);

	// �Ƚ���ǰ��Ա���
	enqueue(&queue, member);

	// ��������
	while (!isEmpty(&queue)) {
		// ����һ����Ա
		FamilyMember *currentMember = dequeue(&queue);

		// ������ǰ��Ա�����к��ӣ����������
		for (int i = 0; i < currentMember->numChildren; i++) {
			// ���ݺ����������Һ��ӳ�Ա
			FamilyMember *child = searchByName(familyTree, currentMember->children[i]);

			// ������ӳ�Ա���ڣ��������
			if (child) {
				enqueue(&queue, child);
			}
		}

		// �Ӹ���/ĸ�׵ĺ����б����Ƴ�
		FamilyMember *parent = findParent(familyTree, currentMember);

		// ����ҵ�����/ĸ��
		if (parent) {
			// ��������/ĸ�׵ĺ����б�
			for (int i = 0; i < parent->numChildren; i++) {
				// �ҵ���ǰ��Ա�ڸ���/ĸ�׺����б��е�λ��
				if (strcmp(parent->children[i], currentMember->name) == 0) {
					// �ͷŵ�ǰ��Ա�ڸ���/ĸ�׺����б��еĿռ�
					free(parent->children[i]);

					// ������ĺ���������ǰ�ƶ�һ��λ��
					for (int j = i; j < parent->numChildren - 1; j++) {
						parent->children[j] = parent->children[j + 1];
					}

					// ���¸���/ĸ�׵ĺ�������
					parent->numChildren--;
					break;
				}
			}
		}


		// �Ӽ������Ƴ�
		int index = findIndexByName(familyTree, currentMember->name);

		// ����ҵ���Ա�ڼ����е�λ��
		if (index != -1) {
			// �ͷŵ�ǰ��Ա���ڴ�
			freeMember(familyTree->members[index]);

			// ������ĳ�Ա������ǰ�ƶ�һ��λ��
			for (int i = index; i < familyTree->numMembers - 1; i++) {
				familyTree->members[i] = familyTree->members[i + 1];
			}

			// ���¼��׳�Ա����
			familyTree->numMembers--;
		}
	}
}


// �Ƴ���Ա������
void removeMember(FamilyTree *familyTree, const char *name) {
	// �������Ƿ�ΪNULL
	if (!familyTree || !name) {
		// ��ӡ������Ϣ����������
		printf("��������\n");
		return;
	}

	// �����������ҳ�Ա
	FamilyMember *member = searchByName(familyTree, name);

	// �����Ա����
	if (member) {
		// ���õݹ�ɾ������
		removeMemberRecursively(familyTree, member);

		// ��ӡ�Ƴ��ɹ�����Ϣ
		printf("%s �������ѴӼ������Ƴ���\n", name);
	} else {
		// ��ӡδ�ҵ���Ա����Ϣ
		printf("δ�ҵ���Ϊ '%s' �ĳ�Ա��\n", name);
	}
}


// ��Ӻ���
void addChild2(FamilyTree *familyTree, const char *parentName, FamilyMember *child) {
	// ��ӡ������Ϣ
	printf("Adding child %s to parent %s in addChild function\n", child->name, parentName);

	// �������Ƿ�ΪNULL
	if (!familyTree || !parentName || !child) {
		// ��ӡ������Ϣ����������
		printf("��������\n");
		return;
	}

	// ���ݸ���/ĸ���������Ҹ���/ĸ�׳�Ա
	FamilyMember *parent = searchByName(familyTree, parentName);

	// �������/ĸ�״���
	if (parent) {
		// ���Ӹ���/ĸ�׵ĺ�������
		parent->numChildren++;

		// ���·��丸��/ĸ�׵ĺ����б���ڴ�
		parent->children = (char **)realloc(parent->children, sizeof(char *) * parent->numChildren);
		if (!parent->children) {
			// ��ӡ������Ϣ���ڴ����ʧ��
			printf("�ڴ����ʧ�ܡ�\n");
			exit(EXIT_FAILURE);
		}

		// ������������ӵ�����/ĸ�׵ĺ����б���
		parent->children[parent->numChildren - 1] = child->name ? strdup(child->name) : NULL;
		if (!parent->children[parent->numChildren - 1]) {
			// ��ӡ������Ϣ���ڴ����ʧ��
			printf("�ڴ����ʧ�ܡ�\n");
			exit(EXIT_FAILURE);
		}

		// ��ӡ�ɹ���Ϣ
		printf("%s �����Ϊ %s �ĺ��ӡ�\n", child->name, parentName);
	} else {
		// ��ӡδ�ҵ�����/ĸ�׵���Ϣ
		printf("δ�ҵ���Ϊ '%s' �ĸ�ĸ��\n", parentName);

		// �ͷź��ӳ�Ա���ڴ�
		freeMember(child);
	}
}


// �ͷż�ͥ��Ա���ڴ�
void freeFamilyTree(FamilyTree *familyTree) {
	// �������Ƿ�ΪNULL
	if (!familyTree) {
		// ��ӡ������Ϣ����������
		printf("��������\n");
		return;
	}

	// �������׳�Ա����
	for (int i = 0; i < familyTree->numMembers; i++) {
		// �ͷų�Ա���ڴ�
		freeMember(familyTree->members[i]);
		// �������еĳ�Աָ����ΪNULL����������ָ��
		familyTree->members[i] = NULL;
	}
}



