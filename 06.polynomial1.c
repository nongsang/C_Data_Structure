#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) ( a > b ? a : b )
#define MAX_DEGREE 101

typedef struct 			// 다항식 구조체 타입 선언
{
	int degree;		// 다항식의 차수
	int coef[MAX_DEGREE];	// 다항식의 계수
} polynomial;

// C = A+B 여기서 A와 B는 다항식이다.
polynomial poly_add1(polynomial A, polynomial B)
{
	polynomial C;				// 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0;	// 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree)
	{
		if (degree_a > degree_b)		// A항 > B항
		{
			C.coef[Cpos++] = A.coef[Apos++];		// 일단 값을 저장하고 ++은 계산 후에
			degree_a--;
		}
		else if (degree_a == degree_b)	// A항 == B항
		{
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else							// B항 > A항
		{
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

int main()
{
	clock_t start, finish;
	double duration;
	polynomial a = { 5,{ 3, 6, 0, 0, 0, 10 } };
	polynomial b = { 4,{ 7, 0, 5, 0, 1 } };
	polynomial c;
	
	start = clock();

	c = poly_add1(a, b);
	printf("%d차항 %d, %d, %d, %d, %d, %d\n", c.degree, c.coef[0], c.coef[1], c.coef[2], c.coef[3], c.coef[4], c.coef[5]);

	finish = clock();
	
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

// 7 ~ 11번 줄
// 차수와 계수를 묶어서 하나의 구조체를 만들었다.
// 다항식은 3x² + 6과 같이 차수와 계수로 나뉘어지는데, 차수와 계수를 한번에 표현할 수가 없다.
// 그렇기 때문에 최고 차수를 알려주고, 각 항에 어떤 값이 들어있는지 알려주는 형식으로 구성하였다.

// 14 ~ 42번 줄
// 두 다항식을 더할 때 저장하는 방법을 정의한다.
// A의 차항과 B의 차항의 백업본을 각 다항식의 연산횟수로 사용한다.
// 두 다항식 차항의 백업본을 비교하여 더 높은 수를 최고 차항으로 저장한다.
// 최고 차항의 차수는 C의 차수가 되고, 각 두 다항식의 차수를 비교하여 같으면 두 값을 더하고 다음 항으로 넘어간다.
// 전부 확인하였으면 C를 반환하는 방식이다.

// 대부분 항의 계수가 0인 3x¹⁴ + 1과 같은 희소 다항식의 경우 공간낭비가 심하다는 단점이 있다.