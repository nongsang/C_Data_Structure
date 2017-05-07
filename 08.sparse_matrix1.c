#include <stdio.h>
#include <time.h>
#define ROWS 3
#define COLS 3

void Sparse_Matrix_Add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS])
{
	int r, c;
	for (r = 0; r < ROWS; ++r)
		for (c = 0; c < COLS; ++c)
			C[r][c] = A[r][c] + B[r][c];
}

int main()
{
	clock_t start, finish;
	double duration;
	int arr1[ROWS][COLS] = { { 2,3,0 },
							 { 8,9,1 },
							 { 7,0,9 } };
	int arr2[ROWS][COLS] = { { 1,0,0 },
							 { 1,0,0 },
							 { 1,0,0 } };
	int arr3[ROWS][COLS];

	start = clock();

	Sparse_Matrix_Add1(arr1, arr2, arr3);

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f �� �Դϴ�.\n", duration);
}

// 6 ~ 12��
// �� ����� ���ؼ� ���ο� ����� �����ϴ� �Լ��̴�.

// 18 ~ 23��
// �� ���ҿ� ���� �״�� �����Ͽ� ����� �����Ѵ�.
// 0�� ���� �������̶�� �ϴ��� �� ���ҿ� ��� ���� �����Ѵ�.