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
	printf("%f 초 입니다.\n", duration);
}

// 6 ~ 12행
// 두 행렬을 더해서 새로운 행렬을 생성하는 함수이다.

// 18 ~ 23행
// 각 원소에 값을 그대로 저장하여 행렬을 생성한다.
// 0이 많은 희소행렬이라고 하더라도 각 원소에 모든 값을 저장한다.