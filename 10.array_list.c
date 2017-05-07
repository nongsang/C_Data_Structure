#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIST_SIZE 100

typedef struct			// �迭�� �̷���� list
{
	int list[MAX_LIST_SIZE];
	int length;
} ArrayList;

void error(const char *massage)		// ���� ����� �Լ�
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

void Init(ArrayList *L)		// �ʱ�ȭ
{
	L->length = 0;
}

int Is_Empty(const ArrayList *L)	// ����ִ��� Ȯ���ϴ� �Լ�
{
	return L->length == 0;
}

int Is_Full(const ArrayList *L)		// �迭�� �� ���ִ��� Ȯ���ϴ� �Լ�
{
	return L->length == MAX_LIST_SIZE;
}

void Display(const ArrayList *L)	// ȭ�鿡 ���
{
	int i;
	for (i = 0; i < L->length; ++i)
		printf("%d\n", L->list[i]);
}

void Add(ArrayList *L, const int position, const int item)		// position��ġ�� item�� �ִ´�
{
	if (!Is_Full(L) && (position >= 0) && (position <= L->length))
	{
		int i;
		for (i = (L->length - 1); i >= position; --i)	// ó���� i���� -1�̹Ƿ� for�� ��ŵ
			L->list[i + 1] = L->list[i];
		L->list[position] = item;
		++L->length;
	}
}

int Delete(ArrayList *L, int position)		// position��ġ�� �ִ� ���� ����
{
	int i;
	int item;

	if (position < 0 || position >= L->length)	// ��ġ�� ��ȿ���� �ʴٸ�
		error("��ġ ����");

	item = L->list[position];		// ���

	for (i = position; i < (L->length - 1); ++i)
		L->list[i] = L->list[i + 1];	// �ڿ� �ִ� ���� ������ �б�
	--L->length;
	return item;		// ������ ���� return
}

int main()
{
	clock_t start, finish;
	double duration;

	ArrayList list;
	ArrayList *plist = (ArrayList*)malloc(sizeof(ArrayList));

	Init(&list);
	Init(plist);

	start = clock();

	Add(&list, 0, 10);
	Add(&list, 0, 20);
	Add(&list, 0, 30);
	Display(&list);

	Add(plist, 0, 10);
	Add(plist, 0, 20);
	Add(plist, 0, 30);
	Display(plist);

	finish = clock();

	free(plist);
	plist = NULL;

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}

// 41 ~ 51��
// position��ġ�� item�� �ִ´�.
//
// 43��
// ����Ʈ�� �ڸ��� �����ְ�, position�� 0�̻��̰�, position�� ������ ����� item�� �����Ѵ�.
//
// 46, 47��
// L->length - 1�� �迭�� ��ġ�� ��Ÿ����.
// ���� �ڿ������� ������ �����ϸ� �տ� �ִ� ���� �ڷ� ��ĭ�� ���������ϴ� ����̴�.
// �� �տ��� ���� ������ i���� -1�̸�, position�� 0�̹Ƿ� for���� �����Ͽ� ���� �߰��Ѵ�.
// ���� ���� ������ i���� position�� ���� ���⿡ for���� 1���� �����Ͽ� ������ ��ĭ �ڷ� ������ ���� �����Ѵ�.
// �� �ڿ� ���� ������ i���� position�� ������ �����Ƿ� for���� �����ϰ� ���� �߰��Ѵ�.

// 53 ~ 67��
// �迭�� ��ġ�� ��ȿ������ ���� �˻��Ѵ�.
// item�� ������ ���� ��ġ�� ���� ����� �����̴�.
// position���� length - 1�� ��ġ���� �ڷΰ��鼭 �ڿ� �ִ� ���� ������ ��ĭ�� ���ܼ� ���������ϴ� ����̴�.

// 74��
// �������� ����Ʈ�� �����Ͽ���.

// 75��
// �������� ����Ʈ�� �����Ͽ���.

// 94 ~ 95��
// �������� ������ ����Ʈ�� �����Ѵ�.