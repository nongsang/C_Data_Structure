#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	clock_t start, finish;
	double duration;
	start = clock();

	// 실행할 코드

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

// 모든 자료구조는 'C언어로 쉽게 풀어 쓴 자료구조', 'C로 쓴 자료구조론', 'C로 배우는 쉬운 자료구조'를 기준으로 코딩한다.

// 알고리즘의 시간을 측정하는 코드다.
// 앞으로 많이 사용할 구조이므로 잘 기억해두도록
