#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct	// 필드
{
	int row;
	int col;
	int value;
} element;

typedef struct
{
	element data[MAX_TERMS];
	int rows;	// 행의 갯수
	int cols;	// 열의 갯수
	int terms;	// 항의 갯수
} SparseMatrix;

SparseMatrix Sparse_Matrix_Add2(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;

	int ca = 0, cb = 0, cc = 0;			// 각 배열의 항목을 가리키는 인덱스
	if (a.rows != b.rows || a.cols != b.cols)
	{
		fprintf(stderr, "희소행렬 크기 에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms)	// 항의 인덱스가 항의 갯수보다 작을때 반복
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
	printf("%f 초 입니다.\n", duration);
}

// 8 ~ 13행
// 필드를 정의한다.
// 몇행 몇열에 어떤 값을 가지고 있는지에 대한 노드이다.

// 15 ~ 21행
// 노드에 대한 테이블을 가진다.
// 필드를 가지고 있으며 추가적으로 행의 갯수와 열의 갯수, 0이 아닌 값을 가진 노드의 갯수를 가진다.

// 23 ~ 69행
// 행렬끼리 더하는 함수이다.
//
// 나중에 한번 알아보도록하자