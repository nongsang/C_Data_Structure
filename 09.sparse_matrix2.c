#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct	// �ʵ�
{
	int row;
	int col;
	int value;
} element;

typedef struct
{
	element data[MAX_TERMS];
	int rows;	// ���� ����
	int cols;	// ���� ����
	int terms;	// ���� ����
} SparseMatrix;

SparseMatrix Sparse_Matrix_Add2(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;

	int ca = 0, cb = 0, cc = 0;			// �� �迭�� �׸��� ����Ű�� �ε���
	if (a.rows != b.rows || a.cols != b.cols)
	{
		fprintf(stderr, "������ ũ�� ����\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms)	// ���� �ε����� ���� �������� ������ �ݺ�
	{
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[ca].col;

		if (inda < indb)
		{
			c.data[cc++] = a.data[ca++];
		}
		else if (inda == indb)
		{
			if ((a.data[ca].value + b.data[cb].value != 0))
			{
				c.data[cc].row = a.data[ca].row;
				c.data[cc].col = a.data[ca].col;
				c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
			}
			else
			{
				++ca;
				++cb;
			}
		}
		else
			c.data[cc++] = b.data[cb++];
	}

	for (; ca < a.terms;)
		c.data[cc++] = a.data[ca++];
	for (; cb < b.terms;)
		c.data[cc++] = b.data[cb++];
	return c;
}

int main()
{
	clock_t start, finish;
	double duration;

	SparseMatrix m1 = { { { 1,1,5 }, { 2,2,9 } }, 3, 3, 2 };
	SparseMatrix m2 = { { { 0,0,5 }, { 2,2,9 } }, 3, 3, 2 };
	SparseMatrix m3;

	start = clock();

	m3 = Sparse_Matrix_Add2(m1, m2);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}

// 8 ~ 13��
// �ʵ带 �����Ѵ�.
// ���� ��� � ���� ������ �ִ����� ���� ����̴�.

// 15 ~ 21��
// ��忡 ���� ���̺��� ������.
// �ʵ带 ������ ������ �߰������� ���� ������ ���� ����, 0�� �ƴ� ���� ���� ����� ������ ������.

// 23 ~ 69��
// ��ĳ��� ���ϴ� �Լ��̴�.
//
// ���߿� �ѹ� �˾ƺ���������