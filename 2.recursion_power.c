#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double power(double dParam, int nParam);
double slow_power(double dParam, int nParam);

int main(void)
{
	clock_t start, finish;
	double duration;
	int i, n = 0;
	start = clock();
	
	for(i = 0; i< 1000000; ++i)
		power(2, 500);			// 재귀를 이용한 거듭제곱 알고리즘

	//for (i = 0; i< 1000000; ++i)
	//	slow_power(2, 500);		// 일반적인 수준의 거듭제곱 알고리즘

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

double power(double dParam, int nParam)
{
	if (0 == nParam)
		return 1;
	else if (0 == (nParam % 2))		// 거듭제곱할 수가 짝수라면
		return power(dParam * dParam, nParam / 2);
	else							// 거듭제곱할 수가 홀수라면
		return dParam * power(dParam * dParam, (nParam - 1) / 2);
}

double slow_power(double dParam, int nParam)
{
	int i;
	double r = 1.0;
	for (i = 0; i < nParam; ++i)	// 거듭제곱할 횟수만큼
		r = r*nParam;				// 값을 곱한다.
	return r;
}

// 16번 줄
// 재귀를 사용한 거듭제곱 함수를 호출하고있다.
// 100만번 반복해서 호출한다.
// 1번만 호출하면 너무 빨라서 시간 측정이 안됨.
// 대략 0.16 ~ 0.17초에 완수한다.

// 19번 줄
// 일반적으로 만들수 있는 거듭제곱 함수를 호출하고 있다.
// 이것도 1번만 호출하면 너무 빨라서 시간측정이 안되기에 100만번 호출.
// 대략 1.2 ~ 1.3초에 완수한다.

// 26 ~ 34번 줄
// 재귀를 사용하여 거듭제곱을 구현하였다.
// xⁿ인 거듭제곱을 (x²)ⁿ/₂으로 표현이 가능하기 때문에 이런 구조가 가능하다.
// n이 짝수의 경우 n이 2로 나눌 수 있기 때문에 (x²)ⁿ/₂로 표현이 가능.
// n이 홀수일 경우 n을 2로 나눌 수 없기 때문에 ⁿ/₂에서 x를 밖으로 빼내어 x * (x²)ⁿ¯¹/₂로 표현할 있다.
// 모든 값은 최종적으로 홀수로 끝나기 때문에 이 홀수를 구하는 식에서 최종값을 도출하게 된다.

// 36 ~ 43번 줄
// 변수를 하나 선언하여 반복해서 값을 곱하고 그 값을 저장하는 방식이다.
// 일반적으로 생각할 수 있는 방식이다.

// 보통 재귀보다 반복이 훨씬 많은 시간과 메모리를 필요로한다.
// 그렇기에 재귀로 간편하게 도식을 세우고 반복을 사용하여 구현하는 것이 일반적이다.
// 다만 여기서는 메모리는 어떨지 몰라도 확실하게 재귀의 속도가 빠르다.

// 차이가 나는 부분은 power(x², ⁿ/₂); 이다.
// 재귀를 호출할 때마다 제곱값과 절반의 거듭제곱할 횟수를 전달한다.
// k번의 순환호출을 해야 값 2ⁿ의 값을 구할 수 있다고 했을 때 k = 2ⁿ를 식으로 나타낼 수 있다.
// 재귀를 호출할 때마다 절반의 거듭제곱할 횟수를 전달하므로 log₂x로 표현할 수 있다.
// 따라서 log₂k = n이므로 거듭제곱할 횟수는 log로 정해진다.

// 하지만 일반적으로 생각할 수 있는 함수는 처음부터 차례대로 100만번 곱하기만 하는 방식이다.
// 거듭제곱할 횟수만큼 for문을 수행하고 100만번을 또 수행한다.
// 매우 비효율적이다. 1/2 혹은 1/3으로 나눠서 수행할 수 있으면 나눠서 하자.