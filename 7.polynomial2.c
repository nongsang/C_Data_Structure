#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERMS 101	// 최대 노드 갯수
struct
{
	double m_coef;		// 계수
	int m_expon;		// 차수
} terms[MAX_TERMS] = { { 8,3 },{ 7,1 },{ 1,0 },{ 10,3 },{ 3,2 },{ 1,0 } };
int avail = 6;	// 저장을 시작할 위치

char Compare(int a, int b)	// 지수를 비교하기 위한 함수
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void Attach(double coef, int expon)	// 계수와 차수를 붙여서 새로운 항을 만든다.
{
	if (avail > MAX_TERMS)
	{
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].m_coef = coef;	// 저장할 위치의 계수 부분에 새로운 계수 저장
	terms[avail++].m_expon = expon;	// 저장할 위치의 차수 부분에 새로운 차수 저장후 다음 위치로 이동
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
	double tempcoef;
	*Cs = avail;		// 결과값을 받을 위치는 avail
	while (As <= Ae && Bs <= Be)
	{
		switch (Compare(terms[As].m_expon, terms[Bs].m_expon))	// 차수를 검사
		{
		case '>':		// 첫번째 항의 차수가 크다면
			Attach(terms[As].m_coef, terms[As].m_expon);	// 첫번째 항의 계수와 차수를 저장한다.
			++As;					// 그리고 다음 위치로 이동
			break;
		case '=':		// 차수가 같다면
			tempcoef = terms[As].m_coef + terms[Bs].m_coef;	// 임시 변수에 계수의 합을 저장
			if (tempcoef)	// 값이 존재하면
				Attach(tempcoef, terms[As].m_expon);	// 임시 변수를 계수로 항을 생성한다.
														// 값이 존재하지 않으면(두 항의 계수를 더하여 0이 나오면) 저장하지 않는다.
			++As;
			++Bs;
			break;
		case '<':		// 두번째 항의 차수가 크면
			Attach(terms[Bs].m_coef, terms[Bs].m_expon);	// 두번째 항의 계수와 차수를 저장한다.
			++Bs;
			break;
		}
	}
	// 둘중 어느 다항식의 연산이 먼저 끝나면(예를 들어 첫번째 다항식이 x^2, 두번째 다항식이 x + a라서 x^2연산만 하고 끝난다면)
	for (; As <= Ae; ++As)			// 남은 첫번째 다항식 전부를 그대로 새로운 항으로 전달
		Attach(terms[As].m_coef, terms[As].m_expon);
	for (; Bs <= Be; ++Bs)			// 남은 두번째 다항식 전부를 그대로 새로운 항으로 전달
		Attach(terms[Bs].m_coef, terms[Bs].m_expon);
	*Ce = avail - 1;	// avail값은 끝에 와서 사용하지 않을 배열의 위치를 가리키므로 아직 유효한 배열의 제일 마지막 원소인 avail - 1 위치를 가리킨다.
}

int main()
{
	int Cs, Ce;
	clock_t start, finish;
	double duration;

	start = clock();

	poly_add2(0, 2, 3, 5, &Cs, &Ce);

	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f 초 입니다.\n", duration);
}

// 6 ~ 10행
// 계수와 차수를 가진 구조체를 정의한다.
// 그리고 구조체를 원소로 가지는 배열을 생성하고 값을 6개 넣는다.

// 13 ~ 18행
// 지수를 비교하기 위한 함수

// 20 ~ 29행
// 지수를 비교하기 위한 함수
//
// 27 ~ 28행
// 계수와 차수를 avail위치에 저장 후에 다음 위치로 이동한다.

// 31 ~ 63행
// 다항식끼리 더해서 값을 도출해내는 함수이다.
// As, Ae는 첫번째 다항식의 배열의 시작 위치와 마지막 위치,
// Bs, Be는 두번째 다항식의 배열의 시작 위치와 마지막 위치,
// Cs, Ce는 새로운 다항식의 배열의 시작 위치와 마지막 위치이다.
//
// 39 ~ 42행
// 첫번째 다항식의 항의 차수가 크다면
// 첫번째 다항식의 항을 그대로 저장한다.
//
// 43 ~ 50행
// 항의 차수가 같다면
// 첫번째 두번째 항의 계수를 더한 계수와 차수로 항을 새롭게 생성하여 저장한다.
//
// 51 ~ 54행
// 두번째 다항식의 항의 차수가 크다면
// 두번째 다항식의 항을 그대로 저장한다.

// 58 ~ 61행
// 조금 어렵다.
// 두 다항식 중 어느 다항식의 계산이 먼저 끝난다면
// 나머지 항을 그대로 새로운 항으로 복사하여 저장한다.
// 예를 들어 첫번째 다항식이 ax², 두번째 다항식이 bx + c라면
// ax²를 그대로 새로운 항으로 복사하고 As가 1이되면서 while문을 빠져나가게 된다.
//
// 58 ~ 59행
// 첫번째 다항식 연산이 먼저 끝나면서 As == 1, Ae == 0이 되면서 스킵한다.
//
// 60 ~ 61행
// 남아있는 항은 두번째 다항식에만 존재하므로
// bx + c를 전부 그대로 새로운 항으로 복사한다.

// 62행
// 항을 새롭게 생성할 때마다 avail이 1씩 증가하며 마지막에는 배열의 마지막 위치값보다 +1된 값을 가진다.
// 따라서 avail - 1을 하여 배열의 마지막위치를 가지게끔 하여 저장한다.