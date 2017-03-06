#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int RecursionBinarySearch(int arr[], int first, int last, int target);

int main(void)
{
	clock_t start, finish;
	double duration;
	int arr[] = { 1, 3, 5, 7, 9 };
	int idx;
	start = clock();

	idx = RecursionBinarySearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 5);
	if (-1 == idx)
		printf("탐색 실패!\n");
	else
		printf("타겟 저장 인덱스 : %d\n", idx);

	idx = RecursionBinarySearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 8);
	if (-1 == idx)
		printf("탐색 실패!\n");
	else
		printf("타겟 저장 인덱스 : %d\n", idx);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

int RecursionBinarySearch(int arr[], int first, int last, int target)	// 재귀함수를 이용한 이진 탐색 알고리즘 함수이다.
{
	int mid;

	if (first > last)			// 범위를 잘 정하게끔
		return -1;
	mid = (first + last) / 2;

	if (target == arr[mid])
		return mid;
	else if (target < arr[mid])
		return RecursionBinarySearch(arr, first, mid - 1, target);		// 재귀함수 사용
	else
		return RecursionBinarySearch(arr, mid + 1, last, target);		// 재귀함수 사용
}

// 재귀함수를 이용한 이진 탐색 알고리즘 함수를 구현한다.

// 32번 줄
// 찾고자 하는 범위를 입력하게끔 수정하였다.

// 36번 줄
// 범위를 거꾸로 적으면 탐색 실패

// 43번 줄
// 찾고자하는 값이 중간보다 앞에 있다면 중간값을 last로 바꿔서 다시 함수를 부른다.

// 45번 줄
// 찾고자하는 값이 중간보다 뒤에 있다면 first를 중간값으로 바꿔서 다시 함수를 부른다.

// 일반 이진 탐색 알고리즘과의 비교
// 나중에 일반 이진탐색 알고리즘과 보면서 비교하도록
// 일반 이진 탐색 알고리즘은 while문을 사용한다.
// 함수 내에서 조건을 만족할 때 까지 반복하는 구조이다.
// 재귀 이진 탐색 알고리즘은 조건에 맞지 않다면 범위를 좁혀서 알고리즘을 다시 호출한다.

// 보기에 깔끔하고 가독성이 좋지만 성능이 좋지 않다.
// 이진 탐색 알고리즘은 일반이 더 좋다.
// 함수를 한번 부르고 함수 내에서 반복하기에 속도면에서 이점이 더 있다.
// 그냥 재귀함수에 익숙해지라고 만든 알고리즘일뿐