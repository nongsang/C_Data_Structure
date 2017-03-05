#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fibonacci(int nParam);
int fibonacci_iter(int nParam);

int main(void)
{
	clock_t start, finish;
	double duration;
	int i, n = 0;
	start = clock();

	//printf("%d\n", fibonacci(40));						// 재귀를 이용한 피보나치 수열
	printf("%d\n", fibonacci_iter(100000000));		// 반복을 이용한 피보나치 수열

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

int fibonacci(int nParam)
{
	if (0 == nParam)
		return 0;
	else if (1 == nParam)
		return 1;
	else
		return fibonacci(nParam - 1) + fibonacci(nParam - 2);
}

int fibonacci_iter(int nParam)
{
	if (nParam < 2)			// 입력값이  0, 1이면
		return nParam;		// 입력값 그대로 반환
	else
	{
		int i, temp, n_1 = 1, n_2 = 0;
		for (i = 2; i <= nParam; ++i)	// 두번째값이 1이기 때문에 n_1값이 1
		{
			temp = n_1;			// (n-1)번째 수를 백업
			n_1 += n_2;			// (n-1)과 (n-2)의 값을 더한다.
			n_2 = temp;			// (n-2)의 값이 (n-1)의 값이 된다.
		}
		return n_1;
	}
}

// 15번 줄
// 재귀로 구현한 피보나치 수열을 호출하였다.
// 하지만 재귀는 너무 많은 자원과 시간을 잡아먹는다.
// 피보나치 수열의 경우 트리구조를 이용하여 매우 쉽게 분석할 수 있다.
// 이진 트리로 표현하고 왼쪽으로 내려가면서 하나씩 채워간다.
// 분석해보면 같은 값을 대입하여 호출하는 경우가 많이 있다.
// 그렇기때문에 성능이 많이 떨어지는 것.
// 40번까지 피보나치 수열을 호출해도 4.38 ~ 4.5초의 완수시간을 가진다.
// 너무 성능이 떨어진다.

// 16번 줄
// 반복으로 구현한 피보나치 수열을 호출하였다.
// 구조는 버블정렬과 비슷한 구조를 이루었음에도 1억번까지 피보나치 수열을 호출했으나 0.22 ~ 0.23초의 완수시간을 가진다.

// 23 ~ 31번 줄
// 0번째와 1번째는 값을 0과 1로만 정의하고 그 이외에는 이전 항들의 합으로 정의하였다.

// 33 ~ 48번 줄
// temp를 사용하여 버블정렬과 같은 구조를 이루어 피보나치를 구축하였다.
// for문 안에 있는 문장이 중요하다.
//
// 42번 줄 n-1번째 항의 값을 백업한다.
// 43번 줄 n-1번째 항과 n-2번째 항을 더하여 n-1번째 항에 저장한다.
// 사실은 n-1번째 항에 결과값을 저장한다는 뜻보다 바로 n번째 항에 더한 값을 던진다라는 뜻으로 이해해야 한다.
// 44번 줄 n-2번째 항에 n-1번째 항과 같은 값을 가진 temp값을 저장한다.
// 이것도 n-2번째 항을 n-1로 인식하게끔한다라고 이해해야한다.

// 27 ~ 30번 줄
// 재귀함수는 많은 함수를 호출하기 때문에 많이 호출되는 함수의 값은 미리 정해주는 것이 속도 향상에 기여한다.
// 이를 동적 프로그래밍(dynamic programming)이라고 한다.
// 알고리즘에서 다시 설명한다.