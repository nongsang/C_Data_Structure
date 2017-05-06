#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101	// 최대 노드 갯수
struct
{
	double m_coef;		// 계수
	int m_expon;		// 차수
} terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
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
	poly_add2(0, 2, 3, 5, &Cs, &Ce);
}