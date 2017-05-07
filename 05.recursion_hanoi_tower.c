#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void HanoiTowerMove(int num, char from, char by, char to);

int main()
{
	clock_t start, finish;
	double duration;
	
	start = clock();

	HanoiTowerMove(10, 'A', 'B', 'C');

	finish = clock();
	
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

void HanoiTowerMove(int num, char from, char by, char to)
{
	if (1 == num)
		printf("원반  1을 %c에서 %c로 이동\n", from, to);			// 원판이 1개라면 바로 목적지로 보낸다.
	else
	{
		HanoiTowerMove(num - 1, from, to, by);					// num - 1개 원판은 from으로 부터 to를 거쳐서 by로 이동하는 재귀함수를 수행
		printf("원반 %2d를 %c에서 %c로 이동\n", num, from, to);
		HanoiTowerMove(num - 1, by, from, to);					// num - 1개 원판은 by로부터 from을 거쳐서 to로 이동하는 재귀함수를 수행
	}
}

// 13번 줄
// 원반의 갯수와 시작지, 경유지, 목적지를 정해주면 원판을 움직인다.

// 20 ~ 30번 줄
// 하노이탑의 문제 풀이를 정의해주었다.
// 가장 간단한 문제로 정의해주면, n개의 원판이 있을 경우
// 1. n-1개의 원판을 경유지에 옮겨놓는다.
// 2. 제일 밑에 있는 원판을 목적지로 옮긴다.
// 3. 경유지에 있는 원판들을 목적지로 옮긴다.
// 세가지로 압축할 수 있다.
//
// n-1개의 원판을 경유지로 옮기는 방법은 마찬가지로,
// 1. n-2개의 원판을 경유지에 옮겨놓는다.
// 2. 제일 밑에 있는 원판을 목적지로 옮긴다.
// 3. 경유지에 있는 원판들을 목적지로 옮긴다.
// 똑같은 풀이 방식이다.
// 이런 재귀를 호출하므로써 호출 방식은 트리 구조를 이루게 된다.
